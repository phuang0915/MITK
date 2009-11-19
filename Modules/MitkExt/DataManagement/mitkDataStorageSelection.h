#ifndef mitkDataStorageSelection_h
#define mitkDataStorageSelection_h

#include <mitkDataStorage.h>
#include <mitkNodePredicateBase.h>
#include <itkEventObject.h>
#include <mitkCommon.h>
#include <set>

namespace mitk
{
  class BaseProperty;
  class PropertyList;

  class MITKEXT_CORE_EXPORT DataStorageSelection: public itk::Object
  {
  public:
    typedef std::vector<mitk::DataTreeNode*> Nodes;
    typedef Message1<const mitk::DataTreeNode*> DataTreeNodeEvent;

    DataTreeNodeEvent NodeChanged;
    DataTreeNodeEvent NodeAdded;
    DataTreeNodeEvent NodeRemoved;
    Message2<const mitk::DataTreeNode*, const mitk::BaseProperty*> PropertyChanged;

    mitkClassMacro(DataStorageSelection, itk::Object);

    mitkNewMacro2Param(DataStorageSelection, DataStorage*, bool);
    mitkNewMacro3Param(DataStorageSelection, DataStorage*, NodePredicateBase*, bool);

    protected:
      DataStorageSelection(mitk::DataStorage* _DataStorage, bool _AutoAddNodes);
      DataStorageSelection(mitk::DataStorage* _DataStorage
        , mitk::NodePredicateBase* _Predicate, bool _AutoAddNodes);

    public:
      virtual ~DataStorageSelection();

      ///
      /// Get the DataStorage.
      ///
      mitk::DataStorage::Pointer GetDataStorage() const;
      ///
      /// Get the predicate.
      ///
      mitk::NodePredicateBase::Pointer GetPredicate() const;
      ///
      /// Returns the size of this selection
      ///
      unsigned int GetSize() const;
      ///
      /// Get node at a specific model index.
      ///
      mitk::DataTreeNode::Pointer GetNode(unsigned int index) const;
      ///
      /// Returns the first node, same as calling GetNode(0)
      ///
      mitk::DataTreeNode::Pointer GetNode() const;
      ///
      /// Returns a copy of the node-vector
      ///
      std::vector<mitk::DataTreeNode*> GetNodes() const;
      ///
      /// \see m_AutoAddNodes
      ///
      bool DoesAutoAddNodes() const;
    public:
      ///
      /// Removes all nodes, sets node as new first element
      ///
      DataStorageSelection& operator=(mitk::DataTreeNode* node);
      ///
      /// Removes all nodes, sets node as new first element
      ///
      DataStorageSelection& operator=(mitk::DataTreeNode::Pointer node);
      ///
      /// Sets the DataStorage.
      ///
      virtual void SetDataStorage(mitk::DataStorage* _DataStorage);
      ///
      /// Sets the predicate. <b>QmitkDataStorageTableModel is owner of the predicate!</b>
      ///
      virtual void SetPredicate(mitk::NodePredicateBase* _Predicate);
      ///
      /// Add a node (if not already there)
      ///
      virtual void AddNode(const mitk::DataTreeNode* node);
      ///
      /// Removes a node
      ///
      virtual void RemoveNode(const mitk::DataTreeNode* node);
      ///
      /// Removes a node
      ///
      virtual void RemoveAllNodes();
      ///
      /// Called whenever an itk Object this class holds gets deleted or modified
      ///
      virtual void ObjectChanged(const itk::Object *caller, const itk::EventObject &event);
    protected:
      ///
      /// Find a node in the list by the given prop
      ///
      mitk::DataTreeNode::Pointer FindNode(const mitk::BaseProperty* prop) const;
      ///
      /// Find a node in the list by the given proplist
      ///
      mitk::DataTreeNode::Pointer FindNode(const mitk::PropertyList* propList) const;
      ///
      /// Removes all nodes and fill the vector again
      ///
      void Reset();
      ///
      /// If a node is already in this list, all listeners will be removed
      ///
      void RemoveListener(mitk::DataTreeNode* node);
      ///
      /// Adds listeners for modified/delete event, for the propertylists
      /// modified/delete and for the modified/delete event of each property
      /// and stores listener tags
      ///
      void AddListener(mitk::DataTreeNode* node);
    protected:
      ///
      /// Pointer to the DataStorage from which the nodes are selected
      ///
      mitk::DataStorage* m_DataStorage;
      ///
      /// DeleteTag for the DataStorage
      ///
      unsigned int m_DataStorageDeletedTag;
      ///
      /// Holds the predicate that defines this SubSet of Nodes. If m_Predicate
      /// is NULL all Nodes will be selected.
      ///
      mitk::NodePredicateBase::Pointer m_Predicate;
      ///
      /// Holds all selected Nodes.
      ///
      std::vector<mitk::DataTreeNode*> m_Nodes;
      ///
      /// \brief Maps a node to a modified observer tag.
      ///
      std::map<mitk::DataTreeNode*, unsigned long> m_NodeModifiedObserverTags;
      ///
      /// \brief Maps a propertylist to a modified observer tag.
      ///
      std::map<mitk::PropertyList*, unsigned long> m_PropertyListModifiedObserverTags;
      ///
      /// \brief Maps a propertylist to a delete observer tag.
      ///
      std::map<mitk::PropertyList*, unsigned long> m_PropertyListDeletedObserverTags;
      ///
      /// \brief Maps a property to  a modified observer tag.
      ///
      std::map<mitk::BaseProperty*, unsigned long> m_PropertyModifiedObserverTags;
      ///
      /// \brief Maps a property to a delete observer tag.
      ///
      std::map<mitk::BaseProperty*, unsigned long> m_PropertyDeletedObserverTags;
      ///
      /// If set to true no event processing will be performed
      ///
      bool m_SelfCall;
      ///
      /// Saves if new nodes are automatically added to this selection
      ///
      bool m_AutoAddNodes;
  };

}

#endif mitkDataStorageSelection_h
