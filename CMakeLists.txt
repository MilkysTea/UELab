cmake_minimum_required(VERSION 3.28)

#设置项目名称
project(UELab)

#设置C++标准
set(CMAKE_CXX_STANDARD 17)

#设置编译参数
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_ANDROID_KHR")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DIMGUI_IMPL_VULKAN_NO_PROTOTYPES")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-compare")

#添加头文件
include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/jni/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/jni/include/Android_draw"
        "${CMAKE_CURRENT_SOURCE_DIR}/jni/include/Android_Graphics"
        "${CMAKE_CURRENT_SOURCE_DIR}/jni/include/Android_my_imgui"
        "${CMAKE_CURRENT_SOURCE_DIR}/jni/include/Android_touch"
        "${CMAKE_CURRENT_SOURCE_DIR}/jni/include/ImGui"
        "${CMAKE_CURRENT_SOURCE_DIR}/jni/include/ImGui/backends"
        "${CMAKE_CURRENT_SOURCE_DIR}/jni/include/My_Utils"
        "${CMAKE_CURRENT_SOURCE_DIR}/jni/include/MyHpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/jni/include/native_surface"
)

#添加源文件
file(GLOB SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/jni/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/jni/src/Android_draw/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/jni/src/Android_Graphics/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/jni/src/Android_my_imgui/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/jni/src/Android_touch/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/jni/src/ImGui/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/jni/src/ImGui/backends/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/jni/src/My_Utils/*.cpp"
)
#生成可执行文件
add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})

#链接库
target_link_libraries(${CMAKE_PROJECT_NAME} log android EGL GLESv3)