/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#include <mitkAnatomicalStructureColorPresets.h>
#include <mitkDICOMSegmentationConstants.h>
#include <mitkDICOMTag.h>
#include <mitkIDICOMTagsOfInterest.h>
#include <mitkLabel.h>
#include <mitkPropertyList.h>
#include <mitkPropertyNameHelper.h>
#include <mitkTemporoSpatialStringProperty.h>

#include <MitkPharmacokineticsExports.h>

#include <mitkDICOMPMConstants.h>

#include <mitkDICOMPMPropertyHelper.h>

// us
#include <usGetModuleContext.h>
#include <usModuleContext.h>

namespace mitk
{
  PropertyList::Pointer DICOMPMPropertyHelper::DeriveDICOMPMProperties()
  {
    PropertyList::Pointer propertyList = PropertyList::New();
    
    // Add DICOM Tag (0008, 0060) Modality "PM"
    propertyList->SetProperty(GeneratePropertyNameForDICOMTag(0x0008, 0x0060).c_str(),
                              TemporoSpatialStringProperty::New("PM"));

    // Add DICOM Tag (0008,103E) Series Description
    propertyList->SetProperty(GeneratePropertyNameForDICOMTag(0x0008, 0x103E).c_str(),
                              TemporoSpatialStringProperty::New("MITK Parameter Map"));
    // Add DICOM Tag (0070,0084) Content Creator Name
    propertyList->SetProperty(GeneratePropertyNameForDICOMTag(0x0070, 0x0084).c_str(),
                              TemporoSpatialStringProperty::New("MITK"));
    // Add DICOM Tag (0012, 0071) Clinical Trial Series ID
    propertyList->SetProperty(GeneratePropertyNameForDICOMTag(0x0012, 0x0071).c_str(),
                              TemporoSpatialStringProperty::New("Session 1"));
    // Add DICOM Tag (0012,0050) Clinical Trial Time Point ID
    propertyList->SetProperty(GeneratePropertyNameForDICOMTag(0x0012, 0x0050).c_str(),
                              TemporoSpatialStringProperty::New("0"));
    // Add DICOM Tag (0012, 0060) Clinical Trial Coordinating Center Name
    propertyList->SetProperty(GeneratePropertyNameForDICOMTag(0x0012, 0x0060).c_str(),
                              TemporoSpatialStringProperty::New("Unknown"));


    return propertyList;
  }


 
} // namespace mitk



