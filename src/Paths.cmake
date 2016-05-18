# Multimodal Interaction Project
#
# Candy Catch
#
# You usually have to change here your system paths

# OpenCV first stage
if(WIN32)
	set(OpenCV_DIR "C:/Users/Scottish-fold/Documents/Visual Studio 2015/Projects/OpenCV/opencv/build")
else()
	set(OpenCV_DIR "/usr/lib/opencv")
endif()

# OpenCV Include dir
set(OpenCV_INCLUDE_DIRS "${OpenCV_DIR}/include")

# OpenCV Library dir
set(OpenCV_LIBS "${OpenCV_DIR}/x64/vc14/lib")

# OpenCV Binary dir
if(WIN32)
	set(OpenCV_BINS "${OpenCV_DIR}/x64/vc14/bin")
else()
	# TODO You need binarys for iOS?? change here
	set(OpenCV_BINS "${OpenCV_DIR}/x64/vc14/bin")
endif()

# Output dir for Debug Binarys
set(DEBUG_BINARY_DIR "${CMAKE_BINARY_DIR}/Debug")

# Output dir for Release Binarys
set(RELEASE_BINARY_DIR "${CMAKE_BINARY_DIR}/Release")