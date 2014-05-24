#include "Container/FilePath.h"

#include <algorithm>
#include <cctype>

// constructors
FilePath::FilePath() {}

FilePath::FilePath( char const *c ) {
    String s( c );
    std::for_each( s.begin(), s.end(), tolower );
    std::replace( s.begin(), s.end(), '\\', '/' );
    _splitpath_s( m_fullPath, nullptr, 0, m_directory, m_directory.MaxLength(), m_fileName, m_fileName.MaxLength(), m_extension, m_extension.MaxLength() );
}

// accessors
String const& FilePath::FullPath() {
    return m_fullPath;
}

String const& FilePath::Drive() {
    return m_drive;
}

String const& FilePath::Directory() {
    return m_directory;
}

String const& FilePath::FileName() {
    return m_fileName;
}

String const& FilePath::Extension() {
    return m_extension;
}

void FilePath::SetDrive( String const &drive ) {
    m_drive = drive;
    _makepath_s( m_fullPath, m_fullPath.MaxLength(), m_drive, m_directory, m_fileName, m_extension );
}

void FilePath::SetDirectory( String const &directory ) {
    m_directory = directory;
    _makepath_s( m_fullPath, m_fullPath.MaxLength(), m_drive, m_directory, m_fileName, m_extension );
}

void FilePath::SetFileName( String const &fileName ) {
    m_fileName = fileName;
    _makepath_s( m_fullPath, m_fullPath.MaxLength(), m_drive, m_directory, m_fileName, m_extension );
}

void FilePath::SetExtension( String const &extension ) {
    m_extension = extension;
    _makepath_s( m_fullPath, m_fullPath.MaxLength(), m_drive, m_directory, m_fileName, m_extension );
}

FilePath::operator char*() {
    return m_fullPath;
}

FilePath::operator char const*() const {
    return m_fullPath;
}