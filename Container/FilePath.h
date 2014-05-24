#ifndef FILE_PATH_H
#define FILE_PATH_H

#include "Container/String.h"

class FilePath {
public:
    // constructors
    FilePath();
    FilePath( char const *c );

    // accessors
    String const& FullPath();
    String const& Drive();
    String const& Directory();
    String const& FileName();
    String const& Extension();
    
    void SetDrive( String const &drive );
    void SetDirectory( String const &directory );
    void SetFileName( String const &fileName );
    void SetExtension( String const &extension );

    operator char*();
    operator char const*() const;

private:
    String m_fullPath;
    String m_drive;
    String m_directory;
    String m_fileName;
    String m_extension;
};

#endif // FILE_PATH_H