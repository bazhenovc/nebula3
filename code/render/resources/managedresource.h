#pragma once
#ifndef RESOURCES_MANAGEDRESOURCE_H
#define RESOURCES_MANAGEDRESOURCE_H
//------------------------------------------------------------------------------
/**
    @class Resources::ManagedResource
    
    ManagedResources are wrappers around actual resource objects and
    are created and managed by the ResourceManager singleton. The actual resource 
    object contained in a ManagedResource may change any time because of the
    resource management performed by the ResourceManager. During
    rendering, the resource client writes render-statistics back into the
    ManagedResource which the resource manager uses as hints for resource management
    (for instance, if an object is appears very small on screen, the 
    ResourceManager can use this information to drop higher resolution
    mip levels freeing up valuable memory for other textures).

    (C) 2007 Radon Labs GmbH
*/
#include "core/refcounted.h"
#include "math/float2.h"
#include "resources/resource.h"

//------------------------------------------------------------------------------
namespace Resources
{
class ManagedResource : public Core::RefCounted
{
    __DeclareClass(ManagedResource);
public:
    /// priority levels
    enum Priority
    {
        HighestPriority = 0,
        HighPriority,
        NormalPriority,
        LowPriority,
        LowestPriority,
    };

    /// constructor
    ManagedResource();
    /// destructor
    virtual ~ManagedResource();

    /// clear render statistics
    void ClearRenderStats();
    /// update render statistics (called by client)
    void UpdateRenderStats(const Math::float2& screenSpaceSize);

    /// set resource id
    void SetResourceId(const ResourceId& id);
    /// get resource id
    const ResourceId& GetResourceId() const;
    /// set contained resource type
    void SetResourceType(const Core::Rtti* rtti);
    /// get contained resource type
    const Core::Rtti* GetResourceType() const;
    /// increment client count
    void IncrClientCount();
    /// decrement client count
    void DecrClientCount();
    /// get current client count
    SizeT GetClientCount() const;
    /// get render count for this frame (number of calls to UpdateRenderStats()
    SizeT GetRenderCount() const;
    /// get maximum screen space size this frame
    const Math::float2& GetMaxScreenSpaceSize() const;
    /// set current priority
    void SetPriority(Priority p);
    /// get the current priority
    Priority GetPriority() const;

    /// get current resource loading state (Initial, Pending, Loaded, Failed, Cancelled)
    Resource::State GetState() const;
    /// get contained resource (may return placeholder)
    const Ptr<Resource>& GetResource() const;
    /// return true if the placeholder resource would be returned
    bool IsPlaceholder() const;
    /// clear the contained resource
    void Clear();

public: // MAY ONLY BE CALLED BY ResourceMappers!
    /// set actual resource
    void SetResource(const Ptr<Resource>& resource);
    /// set place holder resource
    void SetPlaceholder(const Ptr<Resource>& placeholder);

protected:
    ResourceId resourceId;
    Math::float2 maxScreenSpaceSize;
    const Core::Rtti* resType;
    SizeT clientCount;
    SizeT renderCount;
    Priority priority;
    Ptr<Resource> resource;
    Ptr<Resource> placeholder;
};

//------------------------------------------------------------------------------
/**
*/
inline void
ManagedResource::SetResourceId(const ResourceId& id)
{
    this->resourceId = id;
}

//------------------------------------------------------------------------------
/**
*/
inline const ResourceId&
ManagedResource::GetResourceId() const
{
    return this->resourceId;
}

//------------------------------------------------------------------------------
/**
*/
inline void
ManagedResource::SetResourceType(const Core::Rtti* rtti)
{
    n_assert(0 != rtti);
    this->resType = rtti;
}

//------------------------------------------------------------------------------
/**
*/
inline const Core::Rtti*
ManagedResource::GetResourceType() const
{
    n_assert(0 != this->resType);
    return this->resType;
}

//------------------------------------------------------------------------------
/**
*/
inline void
ManagedResource::IncrClientCount()
{
    this->clientCount++;
}

//------------------------------------------------------------------------------
/**
*/
inline void
ManagedResource::DecrClientCount()
{
    n_assert(this->clientCount > 0);
    this->clientCount--;
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
ManagedResource::GetClientCount() const
{
    return this->clientCount;
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
ManagedResource::GetRenderCount() const
{
    return this->renderCount;
}

//------------------------------------------------------------------------------
/**
*/
inline const Math::float2&
ManagedResource::GetMaxScreenSpaceSize() const
{
    return this->maxScreenSpaceSize;
}

//------------------------------------------------------------------------------
/**
*/
inline void
ManagedResource::SetPriority(Priority pri)
{
    this->priority = pri;
}

//------------------------------------------------------------------------------
/**
*/
inline ManagedResource::Priority
ManagedResource::GetPriority() const
{
    return this->priority;
}

//------------------------------------------------------------------------------
/**
*/
inline Resource::State
ManagedResource::GetState() const
{
    if (this->resource.isvalid())
    {
        return this->resource->GetState();
    }
    else
    {
        return Resource::Pending;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline void
ManagedResource::SetResource(const Ptr<Resource>& res)
{
    this->resource = res;
}

//------------------------------------------------------------------------------
/**
*/
inline void
ManagedResource::SetPlaceholder(const Ptr<Resource>& p)
{
    this->placeholder = p;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
ManagedResource::IsPlaceholder() const
{
    return !(this->resource.isvalid());
}

//------------------------------------------------------------------------------
/**
*/
inline const Ptr<Resource>&
ManagedResource::GetResource() const
{
    if (this->resource.isvalid())
    {
        return this->resource;
    }
    else
    {
        return this->placeholder;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline void
ManagedResource::Clear()
{
    this->resource = 0;
    this->placeholder = 0;
}

} // namespace ResourceProxy
//------------------------------------------------------------------------------
#endif
