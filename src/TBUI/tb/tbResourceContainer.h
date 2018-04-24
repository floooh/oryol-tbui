#pragma once
//------------------------------------------------------------------------------
/**
    @class Oryol::_priv::tbResourceContainer
    @ingroup _priv
    @brief in-memory cache for preloaded UI resources
    
    TBUI doesn't support async file loading, thus we need to preload
    all required resources into memory. The interface is similar to
    the gfxResourceContainer.
*/
#include "Core/Containers/Array.h"
#include "Core/Containers/MemoryBuffer.h"
#include "Resource/ResourceRegistry.h"
#include "Resource/ResourceLabelStack.h"
#include "TBUI/TBUISetup.h"

namespace tb {
class TBFile;
};

namespace Oryol {
namespace _priv {

class tbResourceContainer {
public:
    /// constructor
    tbResourceContainer();
    
    /// setup the resource container
    void setup(const TBUISetup& setup);
    /// discard the resource container
    void discard();
    /// lookup resource by locator, return nullptr if not found
    MemoryBuffer* lookupResource(const Locator& loc);
    /// add a resource buffer object (URL must be set!)
    void add(const Locator& loc, MemoryBuffer&& data);

private:
    int uniqueCounter;
    ResourceRegistry registry;
    ResourceLabelStack labelStack;
    Array<MemoryBuffer> resPool;
};

} // namespace _priv
} // namespace Oryol
