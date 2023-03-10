// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef nvs_storage_hpp
#define nvs_storage_hpp

#include <memory>
#include <unordered_map>
#include "nvs.hpp"
#include "nvs_types.hpp"
#include "nvs_page.hpp"
#include "nvs_pagemanager.hpp"
#include "partition.hpp"

//extern void dumpBytes(const uint8_t* data, size_t count);

namespace nvs
{

class Storage : public intrusive_list_node<Storage>
{
    enum class StorageState : uint32_t {
        INVALID,
        ACTIVE,
    };

    struct NamespaceEntry : public intrusive_list_node<NamespaceEntry> {
    public:
        char mName[Item::MAX_KEY_LENGTH + 1];
        uint8_t mIndex;
    };

    typedef intrusive_list<NamespaceEntry> TNamespaces;

    struct UsedPageNode: public intrusive_list_node<UsedPageNode> {
        public: Page* mPage;
    };

    typedef intrusive_list<UsedPageNode> TUsedPageList;

    struct BlobIndexNode: public intrusive_list_node<BlobIndexNode> {
        public:
            char key[Item::MAX_KEY_LENGTH + 1];
            uint8_t nsIndex;
            uint8_t chunkCount;
            VerOffset chunkStart;
    };

    typedef intrusive_list<BlobIndexNode> TBlobIndexList;

public:
    ~Storage();

    Storage(Partition *partition) : mPartition(partition) {
        if (partition == nullptr) {
            abort();
        }
    };

    nvs_err_t init(uint32_t baseSector, uint32_t sectorCount);

    bool isValid() const;

    nvs_err_t createOrOpenNamespace(const char* nsName, bool canCreate, uint8_t& nsIndex);

    nvs_err_t writeItem(uint8_t nsIndex, ItemType datatype, const char* key, const void* data, size_t dataSize);

    nvs_err_t readItem(uint8_t nsIndex, ItemType datatype, const char* key, void* data, size_t dataSize);

    nvs_err_t getItemDataSize(uint8_t nsIndex, ItemType datatype, const char* key, size_t& dataSize);

    nvs_err_t eraseItem(uint8_t nsIndex, ItemType datatype, const char* key);

    template<typename T>
    nvs_err_t writeItem(uint8_t nsIndex, const char* key, const T& value)
    {
        return writeItem(nsIndex, itemTypeOf(value), key, &value, sizeof(value));
    }

    template<typename T>
    nvs_err_t readItem(uint8_t nsIndex, const char* key, T& value)
    {
        return readItem(nsIndex, itemTypeOf(value), key, &value, sizeof(value));
    }

    nvs_err_t eraseItem(uint8_t nsIndex, const char* key)
    {
        return eraseItem(nsIndex, ItemType::ANY, key);
    }

    nvs_err_t eraseNamespace(uint8_t nsIndex);

    const Partition *getPart() const
    {
        return mPartition;
    }

    const char *getPartName() const
    {
        return mPartition->get_partition_name();
    }

    const uint32_t getPartAddress() const
    {
		return mPartition->get_address();
    }

    const uint32_t getPartSize() const
    {
        return mPartition->get_size();
    }

    uint32_t getBaseSector()
    {
        return mPageManager.getBaseSector();
    }

    nvs_err_t writeMultiPageBlob(uint8_t nsIndex, const char* key, const void* data, size_t dataSize, VerOffset chunkStart);

    nvs_err_t readMultiPageBlob(uint8_t nsIndex, const char* key, void* data, size_t dataSize);

    nvs_err_t cmpMultiPageBlob(uint8_t nsIndex, const char* key, const void* data, size_t dataSize);

    nvs_err_t eraseMultiPageBlob(uint8_t nsIndex, const char* key, VerOffset chunkStart = VerOffset::VER_ANY);

    void debugDump();

    void debugCheck();

    nvs_err_t fillStats(nvs_stats_t& nvsStats);

    nvs_err_t calcEntriesInNamespace(uint8_t nsIndex, size_t& usedEntries);

    bool findEntry(nvs_opaque_iterator_t*, const char* name);

    bool nextEntry(nvs_opaque_iterator_t* it);

protected:

    Page& getCurrentPage()
    {
        return mPageManager.back();
    }

    void clearNamespaces();

    nvs_err_t populateBlobIndices(TBlobIndexList&);

    void eraseOrphanDataBlobs(TBlobIndexList&);

    void fillEntryInfo(Item &item, nvs_entry_info_t &info);

    nvs_err_t findItem(uint8_t nsIndex, ItemType datatype, const char* key, Page* &page, Item& item, uint8_t chunkIdx = Page::CHUNK_ANY, VerOffset chunkStart = VerOffset::VER_ANY);

protected:
    Partition *mPartition;
    size_t mPageCount;
    PageManager mPageManager;
    TNamespaces mNamespaces;
    CompressedEnumTable<bool, 1, 256> mNamespaceUsage;
    StorageState mState = StorageState::INVALID;
};

} // namespace nvs

struct nvs_opaque_iterator_t
{
    nvs_type_t type;
    uint8_t nsIndex;
    size_t entryIndex;
    nvs::Storage *storage;
    intrusive_list<nvs::Page>::iterator page;
    nvs_entry_info_t entry_info;
};

#endif /* nvs_storage_hpp */
