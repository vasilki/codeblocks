#ifndef FILEFILTERS_H
#define FILEFILTERS_H

#include <wx/string.h>
#include "settings.h"

/** Provides functions and constants regarding
  * file extension filters present in file dialogs
  * throughout Code::Blocks.
  */
namespace FileFilters
{
    /** @brief Adds file filters for various supported projects and workspaces. */
    DLLIMPORT void AddDefaultFileFilters();

    /** @brief Add a new extension filter.
      * @param name The filter's name.
      * @param mask The extension masks comma-separated string (i.e. "*.cpp,*.c").
      * @return True if added sucessfully, false if not (i.e. empty arguments).
      */
    DLLIMPORT bool Add(const wxString& name, const wxString& mask);

    /** @brief Generates and returns the filter string for use
      * in file dialogs.
      * @param ext If not empty, only filters matching this extension will be returned.
      * Note that @c ext *must* include the separating dot. It can be a full filename
      * if you want, but it *cannot* be just the extension (without the separating dot).
      * @return The filter string.
      */
    DLLIMPORT wxString GetFilterString(const wxString& ext = wxEmptyString);

    /** @brief Generates a simple special filter "All files". No other filters are added.
      * @return the "All files" filter.
      */
    DLLIMPORT wxString GetFilterAll();

    /** @brief Get the filter index for the special "All files" filter.
      * @return the "All files" filter index.
      */
    DLLIMPORT size_t GetIndexForFilterAll();

    // file extension constants
    // *just* the extension, e.g. "exe"
    extern const DLLIMPORT wxString WORKSPACE_EXT;
    extern const DLLIMPORT wxString CODEBLOCKS_EXT;
    extern const DLLIMPORT wxString DEVCPP_EXT;
    extern const DLLIMPORT wxString MSVC6_EXT;
    extern const DLLIMPORT wxString MSVC6_WORKSPACE_EXT;
    extern const DLLIMPORT wxString MSVC7_EXT;
    extern const DLLIMPORT wxString MSVC7_WORKSPACE_EXT;
    extern const DLLIMPORT wxString D_EXT;
    extern const DLLIMPORT wxString F_EXT;
    extern const DLLIMPORT wxString F77_EXT;
    extern const DLLIMPORT wxString F95_EXT;
    extern const DLLIMPORT wxString CPP_EXT;
    extern const DLLIMPORT wxString C_EXT;
    extern const DLLIMPORT wxString CC_EXT;
    extern const DLLIMPORT wxString CXX_EXT;
    extern const DLLIMPORT wxString HPP_EXT;
    extern const DLLIMPORT wxString H_EXT;
    extern const DLLIMPORT wxString HH_EXT;
    extern const DLLIMPORT wxString HXX_EXT;
    extern const DLLIMPORT wxString OBJECT_EXT;
    extern const DLLIMPORT wxString XRCRESOURCE_EXT;
    extern const DLLIMPORT wxString STATICLIB_EXT;
    extern const DLLIMPORT wxString DYNAMICLIB_EXT;
    extern const DLLIMPORT wxString EXECUTABLE_EXT;
    extern const DLLIMPORT wxString RESOURCE_EXT;
    extern const DLLIMPORT wxString RESOURCEBIN_EXT;
    
    // a dot *and* the extension, e.g. ".exe"
    extern const DLLIMPORT wxString WORKSPACE_DOT_EXT;
    extern const DLLIMPORT wxString CODEBLOCKS_DOT_EXT;
    extern const DLLIMPORT wxString DEVCPP_DOT_EXT;
    extern const DLLIMPORT wxString MSVC6_DOT_EXT;
    extern const DLLIMPORT wxString MSVC6_WORKSPACE_DOT_EXT;
    extern const DLLIMPORT wxString MSVC7_DOT_EXT;
    extern const DLLIMPORT wxString MSVC7_WORKSPACE_DOT_EXT;
    extern const DLLIMPORT wxString D_DOT_EXT;
    extern const DLLIMPORT wxString F_DOT_EXT;
    extern const DLLIMPORT wxString F77_DOT_EXT;
    extern const DLLIMPORT wxString F95_DOT_EXT;
    extern const DLLIMPORT wxString CPP_DOT_EXT;
    extern const DLLIMPORT wxString C_DOT_EXT;
    extern const DLLIMPORT wxString CC_DOT_EXT;
    extern const DLLIMPORT wxString CXX_DOT_EXT;
    extern const DLLIMPORT wxString HPP_DOT_EXT;
    extern const DLLIMPORT wxString H_DOT_EXT;
    extern const DLLIMPORT wxString HH_DOT_EXT;
    extern const DLLIMPORT wxString HXX_DOT_EXT;
    extern const DLLIMPORT wxString OBJECT_DOT_EXT;
    extern const DLLIMPORT wxString XRCRESOURCE_DOT_EXT;
    extern const DLLIMPORT wxString STATICLIB_DOT_EXT;
    extern const DLLIMPORT wxString DYNAMICLIB_DOT_EXT;
    extern const DLLIMPORT wxString EXECUTABLE_DOT_EXT;
    extern const DLLIMPORT wxString RESOURCE_DOT_EXT;
    extern const DLLIMPORT wxString RESOURCEBIN_DOT_EXT;
};

#endif // FILEFILTERS_H
