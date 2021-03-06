#
# Name of project
#
PROJECT (Brain)

#
# Need XML from Qt
#
SET(QT_DONT_USE_QTGUI)

#
# Use OpenGL from QT
#
#SET(QT_USE_QTOPENGL TRUE)

#
# Need network
#
SET(QT_USE_QTNETWORK TRUE)

#
# Add QT for includes
#
INCLUDE (${QT_USE_FILE})

#
# Need OpenGL
#
FIND_PACKAGE(OpenGL REQUIRED)
IF (OPENGL_FOUND)
   #
   # Need help finding includes on Apple
   #
   IF (APPLE) 
      # When searching for the include directory, find the location
      # for the OpenGL framework rather than an individual header file.
      FIND_PATH(OPENGL_INCLUDE_DIR OpenGL.framework
        /System/Library/Frameworks
        /Library/Frameworks
        ~/Library/Frameworks
      )
   ENDIF (APPLE)
   #
   # OpenGL Include Directory
   #
   INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
ELSE (OPENGL_FOUND)
   MESSAGE(FATAL_ERROR "OpenGL Libraries were not found")
ENDIF (OPENGL_FOUND)

#
# Create the brain library
#
ADD_LIBRARY(Brain
AnnotationArrangerExecutor.h
AnnotationArrangerInputs.h
AnnotationManager.h
BorderDrawingTypeEnum.h
Brain.h
BrainOpenGL.h
BrainOpenGLAnnotationDrawingFixedPipeline.h
BrainOpenGLChartDrawingInterface.h
BrainOpenGLChartDrawingFixedPipeline.h
BrainOpenGLFixedPipeline.h
BrainOpenGLPrimitiveDrawing.h
BrainOpenGLShape.h
BrainOpenGLShapeCone.h
BrainOpenGLShapeCube.h
BrainOpenGLShapeCylinder.h
BrainOpenGLShapeRing.h
BrainOpenGLShapeRingOutline.h
BrainOpenGLShapeSphere.h
BrainOpenGLTextRenderInterface.h
BrainOpenGLTextureManager.h
BrainOpenGLViewportContent.h
BrainOpenGLVolumeObliqueSliceDrawing.h
BrainOpenGLVolumeSliceDrawing.h
BrainStructure.h
BrainStructureNodeAttributes.h
BrowserTabContent.h
CaretDataFileSelectionModel.h
CaretMappableDataFileAndMapSelectionModel.h
CaretOpenGLInclude.h
ChartingDataManager.h
CiftiConnectivityMatrixDataFileManager.h
CiftiFiberTrajectoryManager.h
ClippingPlaneGroup.h
DisplayProperties.h
DisplayPropertiesAnnotation.h
DisplayPropertiesBorders.h
DisplayPropertiesFiberOrientation.h
DisplayPropertiesFoci.h
DisplayPropertiesImages.h
DisplayPropertiesLabels.h
DisplayPropertiesSurface.h
DisplayPropertiesVolume.h
DummyFontTextRenderer.h
EventAnnotationColorBarGet.h
EventBrainReset.h
EventBrainStructureGetAll.h
EventBrowserTabDelete.h
EventBrowserTabGet.h
EventBrowserTabGetAll.h
EventBrowserTabNew.h
EventCaretMappableDataFileMapsViewedInOverlays.h
EventDataFileAdd.h
EventDataFileDelete.h
EventDataFileRead.h
EventDataFileReload.h
EventGetBrainOpenGLTextRenderer.h
EventIdentificationHighlightLocation.h
EventModelAdd.h
EventModelDelete.h
EventModelGetAll.h
EventModelSurfaceGet.h
EventNodeDataFilesGet.h
EventNodeIdentificationColorsGetFromCharts.h
EventOverlayValidate.h
EventSpecFileReadDataFiles.h
EventSurfacesGet.h
FeatureColoringTypeEnum.h
FiberOrientationSamplesLoader.h
FiberOrientationSamplesVector.h
FiberOrientationSymbolTypeEnum.h
FociDrawingTypeEnum.h
FtglFontTextRenderer.h
GapsAndMargins.h
IdentificationManager.h
IdentificationStringBuilder.h
IdentificationTextGenerator.h
IdentificationWithColor.h
IdentifiedItem.h
IdentifiedItemNode.h
IdentifiedItemVoxel.h
Model.h
ModelChart.h
ModelSurface.h
ModelSurfaceMontage.h
ModelSurfaceSelector.h
ModelTypeEnum.h
ModelVolume.h
ModelWholeBrain.h
Overlay.h
OverlaySet.h
OverlaySetArray.h
ProjectionViewTypeEnum.h
SelectionItemDataTypeEnum.h
SelectionItem.h
SelectionItemAnnotation.h
SelectionItemBorderSurface.h
SelectionItemChartDataSeries.h
SelectionItemChartFrequencySeries.h
SelectionItemChartMatrix.h
SelectionItemChartTimeSeries.h
SelectionItemCiftiConnectivityMatrixRowColumn.h
SelectionItemFocusSurface.h
SelectionItemFocusVolume.h
SelectionItemSurfaceNode.h
SelectionItemSurfaceNodeIdentificationSymbol.h
SelectionItemSurfaceTriangle.h
SelectionItemVoxel.h
SelectionItemVoxelEditing.h
SelectionItemVoxelIdentificationSymbol.h
SelectionManager.h
SessionManager.h
Surface.h
SurfaceDrawingTypeEnum.h
SurfaceMontageConfigurationAbstract.h
SurfaceMontageConfigurationCerebellar.h
SurfaceMontageConfigurationCerebral.h
SurfaceMontageConfigurationTypeEnum.h
SurfaceMontageConfigurationFlatMaps.h
SurfaceMontageLayoutOrientationEnum.h
SurfaceMontageViewport.h
SurfaceNodeColoring.h
SurfaceSelectionModel.h
ViewingTransformations.h
ViewingTransformationsCerebellum.h
ViewingTransformationsVolume.h
VolumeSliceDrawingTypeEnum.h
VolumeSliceSettings.h
VolumeSurfaceOutlineColorOrTabModel.h
VolumeSurfaceOutlineModel.h
VolumeSurfaceOutlineSetModel.h
WholeBrainSurfaceSettings.h
WholeBrainVoxelDrawingMode.h

AnnotationArrangerExecutor.cxx
AnnotationArrangerInputs.cxx
AnnotationManager.cxx
BorderDrawingTypeEnum.cxx
Brain.cxx
BrainOpenGL.cxx
BrainOpenGLAnnotationDrawingFixedPipeline.cxx
BrainOpenGLChartDrawingFixedPipeline.cxx
BrainOpenGLFixedPipeline.cxx
BrainOpenGLPrimitiveDrawing.cxx
BrainOpenGLShape.cxx
BrainOpenGLShapeCone.cxx
BrainOpenGLShapeCube.cxx
BrainOpenGLShapeCylinder.cxx
BrainOpenGLShapeRing.cxx
BrainOpenGLShapeRingOutline.cxx
BrainOpenGLShapeSphere.cxx
BrainOpenGLTextRenderInterface.cxx
BrainOpenGLTextureManager.cxx
BrainOpenGLViewportContent.cxx
BrainOpenGLVolumeObliqueSliceDrawing.cxx
BrainOpenGLVolumeSliceDrawing.cxx
BrainStructure.cxx
BrainStructureNodeAttributes.cxx
BrowserTabContent.cxx
CaretDataFileSelectionModel.cxx
CaretMappableDataFileAndMapSelectionModel.cxx
ChartingDataManager.cxx
CiftiConnectivityMatrixDataFileManager.cxx
CiftiFiberTrajectoryManager.cxx
ClippingPlaneGroup.cxx
DisplayProperties.cxx
DisplayPropertiesAnnotation.cxx
DisplayPropertiesBorders.cxx
DisplayPropertiesFiberOrientation.cxx
DisplayPropertiesFoci.cxx
DisplayPropertiesImages.cxx
DisplayPropertiesLabels.cxx
DisplayPropertiesSurface.cxx
DisplayPropertiesVolume.cxx
DummyFontTextRenderer.cxx
EventAnnotationColorBarGet.cxx
EventBrainReset.cxx
EventBrainStructureGetAll.cxx
EventBrowserTabDelete.cxx
EventBrowserTabGet.cxx
EventBrowserTabGetAll.cxx
EventBrowserTabNew.cxx
EventCaretMappableDataFileMapsViewedInOverlays.cxx
EventDataFileAdd.cxx
EventDataFileDelete.cxx
EventDataFileRead.cxx
EventDataFileReload.cxx
EventGetBrainOpenGLTextRenderer.cxx
EventIdentificationHighlightLocation.cxx
EventModelAdd.cxx
EventModelDelete.cxx
EventModelGetAll.cxx
EventModelSurfaceGet.cxx
EventNodeDataFilesGet.cxx
EventNodeIdentificationColorsGetFromCharts.cxx
EventOverlayValidate.cxx
EventSpecFileReadDataFiles.cxx
EventSurfacesGet.cxx
FeatureColoringTypeEnum.cxx
FiberOrientationSamplesLoader.cxx
FiberOrientationSymbolTypeEnum.cxx
FociDrawingTypeEnum.cxx
FtglFontTextRenderer.cxx
GapsAndMargins.cxx
IdentificationManager.cxx
IdentificationStringBuilder.cxx
IdentificationTextGenerator.cxx
IdentificationWithColor.cxx
IdentifiedItem.cxx
IdentifiedItemNode.cxx
IdentifiedItemVoxel.cxx
Model.cxx
ModelChart.cxx
ModelSurface.cxx
ModelSurfaceMontage.cxx
ModelSurfaceSelector.cxx
ModelTypeEnum.cxx
ModelVolume.cxx
ModelWholeBrain.cxx
Overlay.cxx
OverlaySet.cxx
OverlaySetArray.cxx
ProjectionViewTypeEnum.cxx
SelectionItemDataTypeEnum.cxx
SelectionItem.cxx
SelectionItemAnnotation.cxx
SelectionItemBorderSurface.cxx
SelectionItemChartDataSeries.cxx
SelectionItemChartFrequencySeries.cxx
SelectionItemChartMatrix.cxx
SelectionItemChartTimeSeries.cxx
SelectionItemCiftiConnectivityMatrixRowColumn.cxx
SelectionItemFocusSurface.cxx
SelectionItemFocusVolume.cxx
SelectionItemSurfaceNode.cxx
SelectionItemSurfaceNodeIdentificationSymbol.cxx
SelectionItemSurfaceTriangle.cxx
SelectionItemVoxel.cxx
SelectionItemVoxelIdentificationSymbol.cxx
SelectionItemVoxelEditing.cxx
SelectionManager.cxx
SessionManager.cxx
Surface.cxx
SurfaceDrawingTypeEnum.cxx
SurfaceMontageConfigurationAbstract.cxx
SurfaceMontageConfigurationCerebellar.cxx
SurfaceMontageConfigurationCerebral.cxx
SurfaceMontageConfigurationTypeEnum.cxx
SurfaceMontageConfigurationFlatMaps.cxx
SurfaceMontageLayoutOrientationEnum.cxx
SurfaceMontageViewport.cxx
SurfaceNodeColoring.cxx
SurfaceSelectionModel.cxx
ViewingTransformations.cxx
ViewingTransformationsCerebellum.cxx
ViewingTransformationsVolume.cxx
VolumeSliceDrawingTypeEnum.cxx
VolumeSliceSettings.cxx
VolumeSurfaceOutlineColorOrTabModel.cxx
VolumeSurfaceOutlineModel.cxx
VolumeSurfaceOutlineSetModel.cxx
WholeBrainSurfaceSettings.cxx
WholeBrainVoxelDrawingMode.cxx
) 

#
# Find Headers
#
INCLUDE_DIRECTORIES(
${CMAKE_SOURCE_DIR}/Annotations
${CMAKE_SOURCE_DIR}/Brain
${CMAKE_SOURCE_DIR}/Charting
${CMAKE_SOURCE_DIR}/Cifti
${CMAKE_SOURCE_DIR}/FilesBase
${CMAKE_SOURCE_DIR}/Files
${CMAKE_SOURCE_DIR}/Palette
${CMAKE_SOURCE_DIR}/Gifti
${CMAKE_SOURCE_DIR}/Nifti
${CMAKE_SOURCE_DIR}/Scenes
${CMAKE_SOURCE_DIR}/Xml
${CMAKE_SOURCE_DIR}/Common
)

IF (FREETYPE_FOUND)
INCLUDE_DIRECTORIES(
   ${FTGL_INCLUDE_DIRS}
   ${FREETYPE_INCLUDE_DIR_ft2build}
   ${FREETYPE_INCLUDE_DIR_freetype2}
)
ENDIF (FREETYPE_FOUND)
