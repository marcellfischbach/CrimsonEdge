
add_definitions(-DCE_CORE_EXPORT)
add_definitions(-D_USE_MATH_DEFINES)

set(SOURCES
        class.cc
        class.hh
        classregistry.cc
        classregistry.hh
        defs.hh
        diamond.hh
        coreexport.hh
        coremodule.cc
        coremodule.hh
        engine.cc
        engine.hh
        fps.cc
        fps.hh
        igame.hh
        imodule.hh
        objectregistry.cc
        objectregistry.hh
        outofboundsexception.hh
        settings.cc
        settings.hh
        string.cc
        string.hh
        ticker.cc
        ticker.hh
        time.cc
        time.hh
        types.hh

        animation/skeletonanimation.cc
        animation/skeletonanimation.hh
        animation/skeletonanimationplayer.cc
        animation/skeletonanimationplayer.hh


        entity/camerastate.cc
        entity/camerastate.hh
        entity/collisionstate.cc
        entity/collisionstate.hh
        entity/entity.cc
        entity/entity.hh
        entity/entitystate.cc
        entity/entitystate.hh
        entity/lightstate.cc
        entity/lightstate.hh
        entity/rigidbodystate.cc
        entity/rigidbodystate.hh
        entity/skeletonmeshstate.cc
        entity/skeletonmeshstate.hh
        entity/spatialstate.cc
        entity/spatialstate.hh
        entity/staticcolliderstate.cc
        entity/staticcolliderstate.hh
        entity/staticmeshstate.cc
        entity/staticmeshstate.hh
        entity/terrainmeshstate.cc
        entity/terrainmeshstate.hh
        entity/transform.cc
        entity/transform.hh
        entity/world.cc
        entity/world.hh


        graphics/camera.cc
        graphics/camera.hh
        graphics/defaultframerenderer.cc
        graphics/defaultframerenderer.hh
        graphics/ebufferusage.hh
        graphics/ecomparefunc.hh
        graphics/edatatype.hh
        graphics/efiltermode.hh
        graphics/epixelformat.hh
        graphics/eprimitivetype.hh
        graphics/eprojectionmode.hh
        graphics/erenderpass.hh
        graphics/eshaderattribute.hh
        graphics/etextureaddressmode.hh
        graphics/etexturecomparemode.hh
        graphics/etexturetype.hh
        graphics/etextureunit.hh
        graphics/evertexstream.hh
        graphics/gbuffer.cc
        graphics/gbuffer.hh
        graphics/graphicsexceptions.hh
        graphics/idevice.hh
        graphics/idirectionallight.hh
        graphics/iframerenderer.hh
        graphics/iindexbuffer.hh
        graphics/ilight.hh
        graphics/image.cc
        graphics/image.hh
        graphics/ipointlight.hh
        graphics/irendermesh.hh
        graphics/irenderpipeline.hh
        graphics/irendertarget.hh
        graphics/irendertarget2d.hh
        graphics/irendertarget2darray.hh
        graphics/irendertargetcube.hh
        graphics/iterrainmesh.hh
        graphics/itexture.hh
        graphics/itexture2d.hh
        graphics/itexture2darray.hh
        graphics/itexturecube.hh
        graphics/isampler.hh
        graphics/iskyboxrenderer.hh
        graphics/ivertexbuffer.hh
        graphics/mesh.cc
        graphics/mesh.hh
        graphics/postprocessing.cc
        graphics/postprocessing.hh
        graphics/projector.cc
        graphics/projector.hh
        graphics/samplers.cc
        graphics/samplers.hh
        graphics/skeleton.cc
        graphics/skeleton.hh
        graphics/skeletonmesh.cc
        graphics/skeletonmesh.hh
        graphics/vertexdeclaration.cc
        graphics/vertexdeclaration.hh


        graphics/material/ematerialattributetype.hh
        graphics/material/imaterial.hh
        graphics/material/material.cc
        graphics/material/material.hh
        graphics/material/materialinstance.cc
        graphics/material/materialinstance.hh

        graphics/pp/pp.hh
        graphics/pp/ppcombine.cc
        graphics/pp/ppcombine.hh
        graphics/pp/ppblurh.cc
        graphics/pp/ppblurh.hh
        graphics/pp/ppblurv.cc
        graphics/pp/ppblurv.hh
        graphics/pp/pphighpass.cc
        graphics/pp/pphighpass.hh
        graphics/pp/ppscaledown.cc
        graphics/pp/ppscaledown.hh

        graphics/scene/gfxcamera.cc
        graphics/scene/gfxcamera.hh
        graphics/scene/gfxlight.cc
        graphics/scene/gfxlight.hh
        graphics/scene/gfxmesh.cc
        graphics/scene/gfxmesh.hh
        graphics/scene/gfxmeshcompound.cc
        graphics/scene/gfxmeshcompound.hh
        graphics/scene/gfxoctreescene.cc
        graphics/scene/gfxoctreescene.hh
        graphics/scene/gfxquadtreescene.cc
        graphics/scene/gfxquadtreescene.hh
        graphics/scene/gfxscenecollector.cc
        graphics/scene/gfxscenecollector.hh
        graphics/scene/gfxsimplescene.cc
        graphics/scene/gfxsimplescene.hh
        graphics/scene/igfxscene.hh

        graphics/shadergraph/esgvaluetype.hh
        graphics/shadergraph/sgnode.cc
        graphics/shadergraph/sgnode.hh
        graphics/shadergraph/sgnodes.cc
        graphics/shadergraph/sgnodes.hh
        graphics/shadergraph/shadergraph.cc
        graphics/shadergraph/shadergraph.hh

        graphics/shading/ishader.hh
        graphics/shading/ishaderattribute.hh


        graphics/skybox/simpleskybox.cc
        graphics/skybox/simpleskybox.hh
        graphics/skybox/skyboxmesh.cc
        graphics/skybox/skyboxmesh.hh


        input/iinputsystem.hh
        input/ikeyboard.hh
        input/imouse.hh
        input/input.cc
        input/input.hh
        input/key.hh

        loaders/materialloader.cc
        loaders/materialloader.hh
        loaders/samplerloader.cc
        loaders/samplerloader.hh
        loaders/shadergraphloader.cc
        loaders/shadergraphloader.hh
        loaders/terrainlayerloader.cc
        loaders/terrainlayerloader.hh
        loaders/textfileloader.cc
        loaders/textfileloader.hh
        loaders/textureloader.cc
        loaders/textureloader.hh


        math/boundingbox.cc
        math/boundingbox.hh
        math/color4f.hh
        math/eclippingresult.hh
        math/hysteresis.hh
        math/iclipper.hh
        math/math.hh
        math/matrix.hh
        math/matrix3f.hh
        math/matrix4f.hh
        math/plane.hh
        math/quaternion.hh
        math/randomrange.hh
        math/sphere.hh
        math/vector.hh
        math/vector2f.hh
        math/vector2i.hh
        math/vector3f.hh
        math/vector4f.hh
        math/vector4i.hh

        math/clipper/boxclipper.cc
        math/clipper/boxclipper.hh
        math/clipper/cameraclipper.cc
        math/clipper/cameraclipper.hh
        math/clipper/compoundclipper.cc
        math/clipper/compoundclipper.hh
        math/clipper/multiplaneclipper.cc
        math/clipper/multiplaneclipper.hh
        math/clipper/planeclipper.cc
        math/clipper/planeclipper.hh
        math/clipper/sphereclipper.cc
        math/clipper/sphereclipper.hh

        physics/icollider.hh
        physics/icollisionshape.hh
        physics/iphysicssystem.hh
        physics/iphysicsworld.hh

        resource/assetmanager.cc
        resource/assetmanager.hh
        resource/basecefassetloader.cc
        resource/basecefassetloader.hh
        resource/binarydata.cc
        resource/binarydata.hh
        resource/eaccessmode.hh
        resource/eopenmode.hh
        resource/eseekmode.hh
        resource/file.cc
        resource/file.hh
        resource/filesystemarchive.cc
        resource/filesystemarchive.hh
        resource/filesystemfile.cc
        resource/filesystemfile.hh
        resource/iarchive.hh
        resource/iassetloader.hh
        resource/ifile.hh
        resource/resourceexceptions.hh
        resource/resourcelocator.cc
        resource/resourcelocator.hh
        resource/textfile.cc
        resource/textfile.hh
        resource/vfs.cc
        resource/vfs.hh
        resource/vfsconfigreader.cc
        resource/vfsconfigreader.hh

        #window/wnddesc.hh

        window/iwindow.hh

)


if (${JAVA_BINDINGS})
    SET(SOURCES ${SOURCES}
            engine_java.cc
            java.cc
            java.hh
            java_methods.hh
            game_java.cc
            game_java.hh
            objectregistry_java.cc


            entity/entity_java.cc
            entity/entitystate_java.cc
            entity/javastate.cc
            entity/javastate.hh
            entity/spatialstate_java.cc
            entity/staticmeshstate_java.cc
            entity/world_java.cc

            graphics/idevice_java.cc
            graphics/irendermesh_java.cc
            graphics/itexture_java.cc
            graphics/itexture2d_java.cc
            graphics/mesh_java.cc
            graphics/material/material_java.cc
            graphics/material/materialinstance_java.cc
            graphics/shading/ishader_java.cc
            graphics/shading/ishaderattribute_java.cc

            input/input_java.cc

            resource/assetmanager_java.cc
            resource/javaarchive.cc
            resource/javaarchive.hh
            resource/javafile.cc
            resource/javafile.hh
    )

endif ()


add_library(ceCore SHARED
        ${SOURCES}
)

target_link_libraries(ceCore
        ${PNG_LIBRARIES}
)

if (${JAVA_BINDINGS})
    target_link_libraries(ceCore ${JNI_LIBRARIES})
endif ()

add_dependencies(ceCore ceMOC)
CE_MOC(ceCore)


install(TARGETS ceCore
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
)

install(DIRECTORY . DESTINATION include/ceCore FILES_MATCHING PATTERN "*.hh")



