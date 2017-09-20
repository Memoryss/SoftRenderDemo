#include "IFile.h"

#include <assert.h>

VirtualFile::VirtualFile(int size)
    : m_size(size)
{
    assert(size > 0);
    m_data = new BYTE[size + 1];
    m_data[size] = 0;
}

VirtualFile::~VirtualFile()
{
    Close();
}

int VirtualFile::Size() const
{
    return m_size;
}

void * VirtualFile::GetData()
{
    return m_data;
}

void VirtualFile::Close()
{
    if (NULL != m_data)
    {
        delete[] m_data;
    }

    m_data = NULL;
    m_size = 0;
    m_cursor = 0;
}

int VirtualFile::Read(void *data, int size)
{
    assert(size > 0 && NULL != data);

    if (!IsEOF())
    {
        if (size > m_size - m_cursor)
        {
            size = m_size - m_cursor;
        }

        memcpy(data, &m_data[m_cursor], size);

        m_cursor += size;
        return size;
    }

    return 0;
}

bool VirtualFile::IsEOF() const
{
    return m_cursor >= m_size;
}

DiskFile::DiskFile(const std::string & file)
    : IFile(file)
{
    m_file = fopen(file.c_str(), "rb");
}

DiskFile::~DiskFile()
{
    Close();
}

int DiskFile::Size() const
{
    FILE *fp = m_file;
    if (NULL != fp)
    {
        int size = 0;
        int cur = ftell(fp);

        fseek(fp, 0, SEEK_END);
        size = ftell(fp);
        fseek(fp, cur, SEEK_SET);

        return size;
    }

    return 0;
}

void * DiskFile::GetData()
{
    if (NULL == m_data)
    {
        int size = Size();
        m_data = new BYTE[size + 1];

    }
}

void DiskFile::Close()
{
    if (NULL != m_file)
    {
        fclose(m_file);
        m_file = NULL;
    }

    if (NULL != m_data)
    {
        delete[] m_data;
    }
}

int DiskFile::Read(void *data, int size)
{
    if (NULL != m_file)
    {
        return fread(data, 1, size, m_file);
    }

    return 0;
}

bool DiskFile::IsEOF() const
{
    return m_file == NULL || feof(m_file) != 0;
}
