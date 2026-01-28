#
# 設定 CMake 最低版本要求，確保使用新功能與語法安全
cmake_minimum_required ( VERSION 3.25 )

#
# 為 MSVC 編譯器啟用熱重新載入
if ( POLICY CMP0141 )
  cmake_policy ( SET CMP0141 NEW )
  set ( CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>" )
endif ( )

#
# 定義版本號
set ( ARCHON_VERSION_MAJOR 0 )
set ( ARCHON_VERSION_MINOR 0 )
set ( ARCHON_VERSION_PATCH 1 )
set ( ARCHON_VERSION ${ARCHON_VERSION_MAJOR}.${ARCHON_VERSION_MINOR}.${ARCHON_VERSION_PATCH} )

#
# 指定項目 C++23 作為編譯標準
set ( CMAKE_CXX_STANDARD 23 )
set ( CMAKE_CXX_STANDARD_REQUIRED True )

#
# 統一設定輸出目錄
set ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )
set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )
set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )

#
# 專案相關資訊設定
project ( ARCHON 
  VERSION ${ARCHON_VERSION} 
  DESCRIPTION "CSO-VMware: A CSNZ Virtual Machine Runtime Environment" 
  HOMEPAGE_URL "https://github.com/moubiecat/CSO-VMware" 
  LANGUAGES CXX 
)

#
# 外部庫編譯
add_subdirectory ( external )

#
# 包含頭文件
include_directories ( "${PROJECT_SOURCE_DIR}/include" )
include_directories ( "${PROJECT_SOURCE_DIR}/external/enet/include" )

#
# 客戶端編譯
add_library ( DLL_CLIENT SHARED 
  "${PROJECT_SOURCE_DIR}/src/net.cpp" 
  "${PROJECT_SOURCE_DIR}/src/core.cpp" 
  "${PROJECT_SOURCE_DIR}/src/client.cpp" 
)
target_compile_definitions ( DLL_CLIENT PRIVATE CLIENT_DLL )
target_link_libraries ( DLL_CLIENT PRIVATE enet )
set_target_properties ( DLL_CLIENT PROPERTIES OUTPUT_NAME "csovmware" )

#
# 伺服器編譯
add_executable ( EXE_SERVER 
  "${PROJECT_SOURCE_DIR}/src/net.cpp" 
  "${PROJECT_SOURCE_DIR}/src/core.cpp" 
  "${PROJECT_SOURCE_DIR}/src/server.cpp" 
)
target_link_libraries ( EXE_SERVER PRIVATE enet )
set_target_properties ( EXE_SERVER PROPERTIES 
  OUTPUT_NAME "csovmware_server" 
  LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\" /SUBSYSTEM:CONSOLE" 
)
