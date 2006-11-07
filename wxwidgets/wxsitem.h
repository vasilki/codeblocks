#ifndef WXSITEM_H
#define WXSITEM_H

#include "wxsevents.h"
#include "wxsiteminfo.h"
#include "wxsbaseproperties.h"
#include "wxspredefinedids.h"

#include "../properties/wxsproperties.h"
#include "../wxsresourcetree.h"


class wxsItemRes;
class wxsParent;

/** \brief Base class for all items in resource
 *
 * This class is unified interface for all items which can be used
 * to build wxWidgets resource. These items are:
 * \li \link wxsWidget Standard widgets which can not have child items \endlink
 * \li \link wxsContainer Widgets \ window which can have items inside \endlink
 * \li \link wxsSizer All sizers \endlink
 * \li \link wxsSpacer Spacer \endlink (although this is only one item, it must be threated especially)
 * \li \link wxsTool Tools - items not visible like wxTimer \endlink
 *
 * Each item has two base properties - identifier and variable name. These properties
 * are enabled through wxsFLVariable and wxsFLId flags (declared in wxsglobals.h)
 *
 * Due to some problems with calling virtual functions in constructor, Item
 * is initialized in two steps. First, constructor and than Create function are
 * called. Create is virtual so it could be overridden to use additional
 * setup, but it usually won't be necessarry. In default implementation, it
 * initializes components which are using virtual functions of wxsItem class.
 *
 * Create Function is automatically called inside wxsWidgetFactory class
 * (not wxsWidgetManager !!!), so there's no need to remember about calling that
 * manually.
 *
 * \note Parent of item is automatically set up when adding item to wxsParentClass
 *       using wxsParent::AddChild
 */
class wxsItem: public wxsPropertyContainer
{
    public:

        // Flags used for property filtering
        static const unsigned long flFile     = 0x0001;       ///< \brief Edition in file mode
        static const unsigned long flSource   = 0x0002;       ///< \brief Edition in source mode
        static const unsigned long flMixed    = 0x0004;       ///< \brief Edition in mixed mode
        static const unsigned long flVariable = 0x0008;       ///< \brief Flag turning on variable
        static const unsigned long flId       = 0x0010;       ///< \brief Flag turning on identifier

        /** \brief Ctor
         * \param Resource resource containingthis widget, must not be NULL
         * \param Events array of events used by this object (may be NULL if item doesn't use events)
         */
        wxsItem(wxsItemRes* Resource,const wxsEventDesc* Events,unsigned long PropertiesFlags);

        /** \brief Dctor */
        virtual ~wxsItem();

        /** \brief Getting item info
         *
         * \warning This function should return reference to static variable.
         */
        inline const wxsItemInfo& GetInfo() { return OnGetInfo(); }

        /** \brief Getting event managment object used by this item
         *  \note This function is wrapper to OnGetInfo() protected function
         */
        inline wxsEvents& GetEvents() { return m_Events; }

        /** \brief Getting variable name
         *  \return name of variable or empty string of this item doesn't have one
         */
        inline wxString GetVarName() { return m_VarName; }

        /** \brief Setting variabne name */
        inline void SetVarName(const wxString& NewName) { m_VarName = NewName; }

        /** \brief Getting identifier */
        inline wxString GetIdName() { return m_IdName; }

        /** \brief Setting identifier */
        inline void SetIdName(const wxString& NewIdName) { m_IdName = NewIdName; }

        /** \brief Checking if variable is member of class */
        inline bool GetIsMember() { return m_IsMember; }

        /** \brief Setting IsMember flag */
        inline void SetIsMember(bool NewIsMember) { m_IsMember = NewIsMember; }

        /** \brief Getting parent item */
        inline wxsParent* GetParent() { return m_Parent; }

        /** \brief Getting resource containing this item */
        inline wxsItemRes* GetResource() { return m_Resource; }

        /** \brief Getting item type
         *
         * This function simply calls GetInfo().Type, added to clarify some
         * code parts.
         */
        inline wxsItemType GetType() { return GetInfo().Type; }

        /** \brief Function enumerating properties of this item
         *
         * This function instead of EnumProperties must be declared in
         * items to provide set of it's properties. Content of this function
         * should be exackly the same as content of
         * wxsPropertyContainer::EnumProperties function.
         *
         * \note This function registers properties of parent item and should
         *       be called somewhere in overridden MyEnumProperties.
         */
        void EnumItemProperties(long Flags);

        /** \brief Function generating code creating item in resource
         *  \note This is wrapped for \link OnBuildCreatingCode function
         */
        inline void BuildCreatingCode(wxString& Code,const wxString& WindowParent,wxsCodingLang Language) { return OnBuildCreatingCode(Code,WindowParent,Language); }

        /** \brief Function generating code declaring item (and all it's children)
         *  \note This is wrapped for \link OnBuildCreatingCode function
         */
        inline void BuildDeclarationCode(wxString& Code,wxsCodingLang Language) { return OnBuildDeclarationCode(Code,Language); }

        /** \brief Function enumerating required declaration files
         *  \note This is wrapped for \link OnEnumDeclFiles
         */
        virtual void EnumDeclFiles(wxArrayString& Decl,wxArrayString& Def,wxsCodingLang Language) = 0;

        /** \brief Function building preview for this item
         *
         * This function generates preview using OnBuildPreview
         * and associates it with internal structures.
         * For more details see OnBuildPreview.
         */
        wxObject* BuildPreview(wxWindow* Parent,bool Exact,bool StoreInLastPreview);

        /** \brief Function which should load this item and child items
         *         from xrc / wxs structure
         * \note This is wrapper to OnXmlRead function only
         */
        inline bool XmlRead(TiXmlElement* Element,bool IsXRC,bool IsExtra) { return OnXmlRead(Element,IsXRC,IsExtra); }

        /** \brief Function which should write this item and child items
         *         from xrc / wxs structure
         * \note This is wrapper to OnXmlWrite function only
        */
        virtual bool XmlWrite(TiXmlElement* Element,bool IsXRC,bool IsExtra) { return XmlWrite(Element,IsXRC,IsExtra); }

        /** \brief Function building tree in resource browser for this item
         *
         * This function add item into resource browser and if it's
         * parent for other items, it builds tree for it's children.
         */
        void BuildItemTree(wxsResourceTree* Tree,wxsResourceItemId Parent,int Position=-1);

        /** \brief Function getting lastest tree item id generated in tree
         *
         * \warning returned if may be outdated an may cause some seg faults
         *          when using it.
         */
        inline wxsResourceItemId GetLastTreeItemId() { return m_LastTreeId; }

        /** \brief Function converting this item to wxsParent class.
         *  \return Pointer to wxsParent class or NULL if class hasn't been
         *          derived from it
         */
        virtual wxsParent* ConvertToParent() { return NULL; }

        /** \brief Function returinng pointer to wxsBaseProperties class if item uses it. */
        virtual wxsBaseProperties* GetBaseProps() { return m_BaseProperties; }

        /** \brief Getting current preview object */
        inline wxObject* GetLastPreview() { return m_LastPreview; }

        /** \brief Checking if item is selected inside editor */
        inline bool GetIsSelected() { return m_IsSelected; }

        /** \brief Changking current selection state */
        inline void SetIsSelected(bool NewSelected) { m_IsSelected = NewSelected; }

        /** \brief Checking if node of this item in resource tree is expanded */
        inline bool GetIsExpanded() { return m_IsExpanded; }

        /** \brief Changing currently stored value indicating whether item is expanded in resource tree or not */
        inline void SetIsExpanded(bool NewExpanded) { m_IsExpanded = NewExpanded; }

        /** \brief Clearing selection in this and all child items */
        void ClearSelection();

        /** \brief Easy access to identifier value.
         *
         * This function may be used when building preview to properly
         * set up window identifier.
         * It will return value of identifier given as string, number of it's
         * given as integer or wxID_ANY (-1) if it's user-defined identifier.
         */
        inline wxWindowID GetId() { return wxsPredefinedIDs::Value(m_IdName); }

    protected:

        /** \brief Getting properties availability flags
         *
         * Availability flags are taken from resource object - resource
         * keep information whether it's edited in source / xrc / file mode
         */
        virtual long OnGetPropertiesFlags();

        /** \brief Enumerating item properties */
        virtual void OnEnumItemProperties() = 0;

        /** \brief Function filling up quick properties panel for current item
         *
         * Because wxsItem uses advanced quick properties panel (wxsAdvQPP),
         * it should consist of many wxsAdvQPPChild panels each one configuring
         * group of items. This function is called automatically when panels
         * for this class should be added into quick properties panel.
         *
         * \param QPP wxsAdvQPP class, root Quick properties panel
         */
        virtual void OnAddItemQPP(wxsAdvQPP* QPP) {}

        /** \brief Function building preview for this item
         *
         * This function should generate preview for item and all it's children.
         *
         * There are two types of preview:
         *  \li Preview in editor
         *  \li Exact preview used after "Show preview" button is pressed.
         *
         * In most cases both previews should be exackly the same, only in case
         * of sizers there are some additional borders around to visually show
         * placement of sizers.
         *
         * Exact preview should look exackly like it will be shown in real
         * application, and the code creating preview should be simillar to
         * code generated in BuildCreatingCode function.
         *
         * \param Parent wxWidgets object for this one
         * \param Exact true when this preview should be exact one, false otherwise
         * \return Newly created object
         * \note This function is called from BuildPreview() function
         */
        virtual wxObject* OnBuildPreview(wxWindow* Parent,bool Exact) = 0;

        /** \brief Function generating code creating item in resource
         *
         * This function should generate code creating new wxWidgets object and
         * initializing it (but not declaring the code itself). New code should
         * be appended at the end of string passed in Code parameter.
         *
         * You should not worry about the coding style used in generated code.
         * Code will be restyled before putting into files. Just keep it in
         * valid syntax.
         *
         * \param Code string where new code should be appended. Do not even try
         *        to mess up with current content.
         * \param WindowParent name of parent of class wxWindow* (this argument
         *        may be passed as parent in wxWidgets constructors. It will be
         *        empty string for root items.
         * \param Language language of generated code
         */
        virtual void OnBuildCreatingCode(wxString& Code,const wxString& WindowParent,wxsCodingLang Language) = 0;

        /** \brief Function generating code declaring item (and all it's children)
         *
         * This function should append new code with item pointer declaration,
         * for example: \code wxButton* Button1; \endcode at the end of code passed
         * in Code parameter. If declaration is not needed, Code should be left
         * as is.
         *
         * Default implementation uses name of widget taken from GetInfo
         * function. So overriding this funciton will most probably take
         * place in case of spacer whch doesn't have variable at all.
         */
        virtual void OnBuildDeclarationCode(wxString& Code,wxsCodingLang Language);

        /** \brief Function enumerating required declaration files
         *
         * This function is called when generating source code. It must add
         * required declaration files (f.ex. header files in case of c++) into
         * given lists.
         * There are two lists of files - one is list used for class declaration
         * and one for class definition. The first one must contain header files required
         * when creating class (f.ex. <wx/button.h>, second one when creating content
         * of resource (f.ex. <wx/bitmap.h>). If You're unsure of type, use the first one.
         */
        virtual void OnEnumDeclFiles(wxArrayString& Decl,wxArrayString& Def,wxsCodingLang Language) = 0;

        /** \brief Function which should load this item and child items
         *         from xrc / wxs structure
         *
         * Default implementation loads base properties using
         * wxsPropertyContainer::XmlRead() function and loads extra data from
         * node passed as argument using defautl scheme.
         *
         * \param Element element containing configuration for this item
         * \param IsXRC if true, this function should load XRC structure from
         *        this node and if it's parent, it should load all children.
         * \param IsExtra if true, this function should load Extra informations
         *        not conforming to XRC standard from given Xml element.

         * \note This function will be called twice when loading resource which
         *       uses additional XRC file because XRC structure data and extra
         *       data are in separate files.
         */
        virtual bool OnXmlRead(TiXmlElement* Element,bool IsXRC,bool IsExtra);

        /** \brief Function which should write this item and child items
         *         from xrc / wxs structure
         *
         * \param Element here all item configuration should be stored
         * \param IsXRC if true, this function should write XRC structure to
         *        this node and if it's parent, it should write all children.
         * \param IsExtra if true, this function should write Extra informations
         *        not conforming to XRC standard to given Xml element.

         * \note This function will be called twice when saving Sresource which
         *       uses additional XRC file because XRC structure data and extra
         *       data are in separate files.
         */
        virtual bool OnXmlWrite(TiXmlElement* Element,bool IsXRC,bool IsExtra);

        /** \brief Getting item info
         *
         * \warning This function should return reference to static variable.
         * \note It may be memory-consuming to create wxsItemInfo for each instance of class,
         *       it's better to crate one for all classes
         */
        virtual const wxsItemInfo& OnGetInfo() = 0;

    private:

        /** \brief Function enumerating proeprties
         *
         * This function changes a little bit the convention of creating
         * properties in wxsPropertyContainer. If item has parent, parent is
         * responsible for creating properties of it's child and because of
         * that, it may add it's own additional properties. Child properties
         * are enumerated using MyEnumProperties function.
         */
        virtual void OnEnumProperties(long Flags);

        /** \brief Building Quick properties panel.
         *
         * Items always create wxsAdvQPP class. wxsAdvQPPChild classes may be
         * added from his item and from it's parent, so the process of adding
         * wxsAdvQPPChild classes is controlled by item's parent, just like in
         * case of properties.
         */
        virtual wxsQuickPropsPanel* OnCreateQuickProperties(wxWindow* Parent);

        /** \brief Handler for change notifications */
        virtual void OnPropertyChanged();

        /** \brief Additional hangled for sub properties */
        virtual void OnSubPropertyChanged(wxsPropertyContainer*);

        wxsEvents m_Events;                     ///< \brief Object managing events
        wxsParent* m_Parent;                    ///< \brief Parent class of this one
        wxsItemRes* m_Resource;                 ///< \brief Resource containing this item
        wxString m_VarName;                     ///< \brief Variable name
        wxString m_IdName;                      ///< \brief Name of identifier
        bool m_IsMember;                        ///< \brief Swith between local and global variable
        wxsBaseProperties* m_BaseProperties;    ///< \brief Pointer to base properties if item uses it
        unsigned long m_PropertiesFlags;        ///< \brief Properties flags
        wxObject* m_LastPreview;                ///< \brief Current preview object
        bool m_IsSelected;                      ///< \brief Set to true if item is selected inside editor
        bool m_IsExpanded;                      ///< \brief Set to true if corresponding node in resource tree is expanded,
                                                ///         this value may not always be correct, it's used when recreating
                                                ///         resource tree after change
        wxsResourceItemId m_LastTreeId;         ///< \brief Last Tree item id generated from BuildItemTree
};

#endif
