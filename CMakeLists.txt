project(Rubix)

add_library(Rubix RubixMain.h RubixMain.cpp Ops_Matrix.h Ops_Matrix.cpp CLManager.h CLManager.cpp Compute_Object.h Compute_Object.cpp LogHandler.h LogHandler.cpp ThreadWrap.h ThreadWrap.cpp Dtype.cpp Dtype.h Matrix_Add_Kernels.cl Matrix_Subtr_Kernels.cl Matrix_Mult_Kernels.cl Matrix_Div_Kernels.cl MatrixStorage.h MatrixStorage.cpp Tensor.cpp Tensor.h Matrix.cpp Matrix.h MatrixLayout.h MatrixLayout.cpp)

#find_package(OpenCL REQUIRED)

target_include_directories(Rubix PRIVATE "${./OpenCL/include/CL}")

target_link_libraries(Rubix PRIVATE "${./OpenCL/lib}")

target_link_libraries(Rubix PUBLIC compiler_flags)

target_include_directories(Rubix INTERFACE ${./})

