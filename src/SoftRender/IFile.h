#ifndef __IFILE_H__
#define __IFILE_H__

#include <string>
#include "stdio.h"

#define BYTE unsigned char

class IFile
{
public:
    IFile() {}
    IFile(const std::string &source) : m_source(source) {}

    virtual ~IFile() {}

    const std::string & GetSource() { return m_source; }

    virtual int Size() const = 0;

    virtual void * GetData() = 0;

    virtual void Close() = 0;

    virtual int Read(void *data, int size) = 0;

    virtual bool IsEOF() const = 0;

protected:
    std::string m_source;
};

class VirtualFile : public IFile
{
public:
    VirtualFile(int size);
    virtual ~VirtualFile();

    virtual int Size() const;

    virtual void * GetData();

    virtual void Close();
    
    virtual int Read(void *data, int size);

    virtual bool IsEOF() const;

protected:
    int m_size{ 0 };
    BYTE *m_data{ NULL };
    int m_cursor{ 0 };
};

class DiskFile : public IFile
{
public:
    DiskFile(const std::string & file);
    virtual ~DiskFile();

    virtual int Size() const;

    virtual void * GetData();

    virtual void Close();

    virtual int Read(void *data, int size);

    virtual bool IsEOF() const;

protected:
    FILE *m_file{ NULL };
    BYTE *m_data{ NULL };
};

#endif
