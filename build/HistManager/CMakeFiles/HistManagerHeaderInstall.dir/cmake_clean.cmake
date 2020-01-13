file(REMOVE_RECURSE
  "../x86_64-centos7-gcc8-opt/include/HistManager"
  "../x86_64-centos7-gcc8-opt/include/HistManager"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/HistManagerHeaderInstall.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
