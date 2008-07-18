#pragma once
#ifndef TEST_COREGRAPHICSTEST_H
#define TEST_COREGRAPHICSTEST_H
//------------------------------------------------------------------------------
/** 
    @class Test::CoreGraphicsTest
    
    Base class for test cases which needs a CoreGraphics environment.
    
    (C) 2007 Radon Labs GmbH
*/
#include "testbase/testcase.h"
#include "io/ioserver.h"
#include "interface/iointerface.h"
#include "coregraphics/displaydevice.h"
#include "coregraphics/renderdevice.h"
#include "coregraphics/shaderserver.h"
#include "resources/sharedresourceserver.h"
#include "resources/resourcemanager.h"

//------------------------------------------------------------------------------
namespace Test
{
class CoreGraphicsTest : public Test::TestCase
{
    DeclareClass(CoreGraphicsTest);
protected:
    /// setup the required runtime
    bool SetupRuntime();
    /// shutdown the runtime
    void ShutdownRuntime();

    Ptr<IO::IoServer> ioServer;
    Ptr<Interface::IOInterface> ioInterface;
    Ptr<Resources::SharedResourceServer> resServer;
    Ptr<Resources::ResourceManager> resManager;
    Ptr<CoreGraphics::DisplayDevice> displayDevice;
    Ptr<CoreGraphics::RenderDevice> renderDevice;
    Ptr<CoreGraphics::ShaderServer> shaderServer;
};

} // namespace Test    
//------------------------------------------------------------------------------
#endif
