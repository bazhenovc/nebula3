//------------------------------------------------------------------------------
//  fileservertest.cc
//  (C) 2006 Radon Labs GmbH
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "fileservertest.h"
#include "io/ioserver.h"
#include "io/assign.h"
#include "io/filestream.h"
#include "io/binarywriter.h"
#include "io/binaryreader.h"
#include "core/ptr.h"

namespace Test
{
ImplementClass(Test::FileServerTest, 'FSRT', Test::TestCase);

using namespace IO;
using namespace Util;

//------------------------------------------------------------------------------
/**
*/
void
FileServerTest::Run()
{
    Ptr<IoServer> ioServer = IoServer::Create();
    ioServer->RegisterUriScheme("file", FileStream::RTTI);

    // check for standard assigns
    this->Verify(ioServer->HasAssign("home"));
    this->Verify(ioServer->HasAssign("bin"));
    this->Verify(!ioServer->HasAssign("test"));
    this->Verify(ioServer->HasAssign("temp"));
    #if __WIN32__
    this->Verify(ioServer->HasAssign("user"));
    #endif

    // add a new assign
    ioServer->SetAssign(Assign("test", "file:///c:/temp"));
    this->Verify(ioServer->HasAssign("test"));
    this->Verify(ioServer->GetAssign("test") == "file:///c:/temp");

    // test assign resolution
    this->Verify(ioServer->ResolveAssigns("test:bla.txt") == "file:///c:/temp/bla.txt");

    // set test assign to another location
    ioServer->SetAssign(Assign("test", "temp:"));
    this->Verify(ioServer->GetAssign("test") == "temp:");

    #if __WIN32__
    // create a test directory in test:
    this->Verify(ioServer->CreateDirectory("test:one/two"));
    ioServer->SetAssign(Assign("test", "temp:one/two"));
    this->Verify(ioServer->DirectoryExists("temp:one"));
    this->Verify(ioServer->DirectoryExists("temp:one/two"));
    this->Verify(!ioServer->DirectoryExists("temp:one/two/three"));
    this->Verify(!ioServer->FileExists("temp:one"));

    // create a file in the test directory
    Ptr<Stream> file = ioServer->CreateStream("test:file1");
    file->SetAccessMode(Stream::WriteAccess);
    this->Verify(file->Open());

    Ptr<BinaryWriter> writer = BinaryWriter::Create();
    writer->SetStream(file);
    this->Verify(writer->Open());
    writer->WriteChar('A');
    writer->WriteChar('B');
    writer->WriteChar('C');
    writer->WriteChar('\n');
    writer->Close();
    file->Close();

    // test if file exists
    this->Verify(ioServer->FileExists("test:file1"));
    this->Verify(!ioServer->FileExists("test:file2"));
    this->Verify(!ioServer->DirectoryExists("test:file1"));

    // copy file
    this->Verify(ioServer->CopyFile("test:file1", "test:file2"));
    this->Verify(ioServer->FileExists("test:file2"));
    this->Verify(ioServer->ComputeFileCrc("test:file1") == ioServer->ComputeFileCrc("test:file2"));
    
    // check copied contents
    file->SetURI("test:file2");
    file->SetAccessMode(Stream::ReadAccess);
    this->Verify(file->Open());

    Ptr<BinaryReader> reader = BinaryReader::Create();
    reader->SetStream(file);
    this->Verify(reader->Open());
    this->Verify(reader->ReadChar() == 'A');
    this->Verify(reader->ReadChar() == 'B');
    this->Verify(reader->ReadChar() == 'C');
    this->Verify(reader->ReadChar() == '\n');
    this->Verify(file->Eof());
    reader->Close();
    file->Close();

    this->Verify(!ioServer->IsReadOnly("test:file2"));
    ioServer->SetReadOnly("test:file2", true);
    this->Verify(ioServer->IsReadOnly("test:file2"));
    ioServer->SetReadOnly("test:file2", false);
    this->Verify(!ioServer->IsReadOnly("test:file2"));

    // test directory listing
    this->Verify(ioServer->CreateDirectory("temp:one/anotherdir"));
    Array<String> list = ioServer->ListFiles("temp:one/two", "*");
    this->Verify(list.Size() == 2);
    list = ioServer->ListDirectories("temp:one/two", "*");
    this->Verify(list.Size() == 0);
    list = ioServer->ListFiles("temp:one", "*");
    this->Verify(list.Size() == 0);
    list = ioServer->ListDirectories("temp:one", "*");
    this->Verify(list.Size() == 2);

    // test file deleting
    this->Verify(ioServer->DeleteFile("temp:one/two/file1"));
    this->Verify(!ioServer->FileExists("temp:one/two/file1"));
    this->Verify(!ioServer->DeleteDirectory("temp:one/two"));
    this->Verify(ioServer->DeleteFile("temp:one/two/file2"));
    this->Verify(ioServer->DeleteDirectory("temp:one/two"));
    this->Verify(!ioServer->DirectoryExists("temp:one/two"));
    this->Verify(ioServer->DeleteDirectory("temp:one/anotherdir"));
    this->Verify(ioServer->DeleteDirectory("temp:one"));
    #endif
}

}; // namespace Test
