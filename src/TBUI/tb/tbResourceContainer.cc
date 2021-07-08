//------------------------------------------------------------------------------
//  tbResourceContainer.cc
//------------------------------------------------------------------------------
#include "Pre.h"
#include "tbResourceContainer.h"

namespace Oryol {
namespace _priv {

//------------------------------------------------------------------------------
tbResourceContainer::tbResourceContainer() :
uniqueCounter(0) {
    // empty
}

//------------------------------------------------------------------------------
void
tbResourceContainer::setup(const TBUISetup& setup) {
    this->resPool.Reserve(setup.ResourcePoolSize);
    this->resPool.SetAllocStrategy(0, 0);
    this->registry.Setup(setup.ResourceRegistryCapacity);
    this->labelStack.Setup(setup.ResourceLabelStackCapacity);
}

//------------------------------------------------------------------------------
void
tbResourceContainer::discard() {
    this->resPool.Clear();
    this->registry.Discard();
    this->labelStack.Discard();
}

//------------------------------------------------------------------------------
void
tbResourceContainer::add(const Locator& loc, MemoryBuffer&& data) {
    Id id = this->registry.Lookup(loc);
    if (id.IsValid()) {
        Log::Warn("TBUIResourceContainer::Add(): resource '%s' already exists!\n", loc.Location().AsCStr());
    }
    else {
        Id newId(this->uniqueCounter++, this->resPool.Size(), 0);
        this->registry.Add(loc, newId, this->labelStack.PeekLabel());
        this->resPool.Add(std::move(data));
    }
}

//------------------------------------------------------------------------------
MemoryBuffer*
tbResourceContainer::lookupResource(const Locator& loc) {
    Id id = this->registry.Lookup(loc);
    if (id.IsValid()) {
        return &(resPool[id.SlotIndex]);
    }
    else {
        return nullptr;
    }
}

} // namespace _priv
} // namespace Oryol
