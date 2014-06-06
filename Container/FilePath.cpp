#include "Container/FilePath.h"
#include <algorithm>
#include <cctype>

// constructors
FilePath::FilePath() {}

FilePath::FilePath( char const *c ) {
    String s( c );
    for( char &ch : s )
        ch = tolower( ch );
    std::replace( s.begin(), s.end(), '\\', '/' );
    _splitpath_s( s, m_drive, m_drive.MaxLength(), m_directory, m_directory.MaxLength(), m_fileName, m_fileName.MaxLength(), m_extension, m_extension.MaxLength() );
    m_fullPath = m_drive + m_directory + m_fileName + m_extension;
}

// accessors
String const& FilePath::FullPath() const {
    return m_fullPath;
}

String const& FilePath::Drive() const {
    return m_drive;
}

String const& FilePath::Directory() const {
    return m_directory;
}

String const& FilePath::FileName() const {
    return m_fileName;
}

String const& FilePath::Extension() const {
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