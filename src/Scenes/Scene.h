#ifndef __SCENE__H_
#define __SCENE__H_

/*LICENSE_START*/
/*
 *  Copyright (C) 2014  Washington University School of Medicine
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
/*LICENSE_END*/


#include "CaretObject.h"
#include "SceneTypeEnum.h"

namespace caret {
    class SceneAttributes;
    class SceneClass;
    class SceneInfo;
    
    class Scene : public CaretObject {
        
    public:
        Scene(const SceneTypeEnum::Enum sceneType);
        
        virtual ~Scene();
        
    private:
        Scene(const Scene&);

        Scene& operator=(const Scene&);
        
    public:

        const SceneAttributes* getAttributes() const;

        SceneAttributes* getAttributes();

        void addClass(SceneClass* sceneClass);
        
        int32_t getNumberOfClasses() const;
        
        const SceneClass* getClassAtIndex(const int32_t indx) const;

        const SceneClass* getClassWithName(const AString& sceneClassName) const;
        
        AString getName() const;

        void setName(const AString& sceneName);

        AString getBalsaSceneID() const;
        
        void setBalsaSceneID(const AString& balsaSceneID);
        
        AString getDescription() const;
        
        void setDescription(const AString& description);
        
        SceneInfo* getSceneInfo();
        
        const SceneInfo* getSceneInfo() const;
        
        void setSceneInfo(SceneInfo* sceneInfo);
        
        bool hasFilesWithRemotePaths() const;
        
        void setHasFilesWithRemotePaths(const bool hasFilesWithRemotePaths);

        
        // ADD_NEW_METHODS_HERE

        static void setSceneBeingCreated(Scene* scene);
        
        static void setSceneBeingCreatedHasFilesWithRemotePaths();
        
    private:

        /** Attributes of the scene*/
        SceneAttributes* m_sceneAttributes;

        /** Classes contained in the scene*/
        std::vector<SceneClass*> m_sceneClasses;

        /** Info about scene */
        SceneInfo* m_sceneInfo;
        
        /** True if it found a ScenePathName with a remote file */
        bool m_hasFilesWithRemotePaths;
        
        /** When a scene is being created, this will be set */
        static Scene* s_sceneBeingCreated;
        
        // ADD_NEW_MEMBERS_HERE

    };
    
#ifdef __SCENE_DECLARE__
    Scene* Scene::s_sceneBeingCreated = NULL;
#endif // __SCENE_DECLARE__

} // namespace
#endif  //__SCENE__H_
