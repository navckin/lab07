[![Build Status](https://travis-ci.com/navckin/lab06.svg?branch=main)](https://travis-ci.com/navckin/lab06)
## Laboratory work VI

Данная лабораторная работа посвещена изучению средств пакетирования на примере **CPack**

```sh
$ open https://cmake.org/Wiki/CMake:CPackPackageGenerators
```

## Tasks

- [x] 1. Создать публичный репозиторий с названием **lab06** на сервисе **GitHub**
- [x] 2. Выполнить инструкцию учебного материала
- [x] 3. Ознакомиться со ссылками учебного материала
- [x] 4. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial
1 создаем переменную GITHUB_USERNAME со значением, указанным после равно 2 создаем переменную GITHUB_EMAIL со значением, указанным после равно 3 создаем псевдоним для vim - edit
```sh
$ export GITHUB_USERNAME=<имя_пользователя>
$ export GITHUB_EMAIL=<адрес_почтового_ящика>
$ alias edit=<nano|vi|vim|subl>
$ alias gsed=sed # for *-nix system
```
1 перемещаемся в д-ию workspace 2 сохр. указ. папку 3 активируем сорс
```sh
$ cd ${GITHUB_USERNAME}/workspace
$ pushd .
$ source scripts/activate
```
1 клонируем лаб 05 в 06 2 перемещаемся в д-юю лаб 06 
```sh
$ git clone https://github.com/${GITHUB_USERNAME}/lab05 projects/lab06
$ cd projects/lab06
$ git remote remove origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab06
```
в указанный файл дописываем указ. строки
git diff - просмотр отличий локальной версии от последнего коммита
```sh
$ gsed -i '/project(print)/a\
set(PRINT_VERSION_STRING "v\${PRINT_VERSION}")
' CMakeLists.txt
$ gsed -i '/project(print)/a\
set(PRINT_VERSION\
  \${PRINT_VERSION_MAJOR}.\${PRINT_VERSION_MINOR}.\${PRINT_VERSION_PATCH}.\${PRINT_VERSION_TWEAK})
' CMakeLists.txt
$ gsed -i '/project(print)/a\
set(PRINT_VERSION_TWEAK 0)
' CMakeLists.txt
$ gsed -i '/project(print)/a\
set(PRINT_VERSION_PATCH 0)
' CMakeLists.txt
$ gsed -i '/project(print)/a\
set(PRINT_VERSION_MINOR 1)
' CMakeLists.txt
$ gsed -i '/project(print)/a\
set(PRINT_VERSION_MAJOR 0)
' CMakeLists.txt
$ git diff
```
созадем файл и редактируем его, заполянем данными
```sh
$ touch DESCRIPTION && edit DESCRIPTION
$ touch ChangeLog.md
$ export DATE="`LANG=en_US date +'%a %b %d %Y'`"
$ cat > ChangeLog.md <<EOF
* ${DATE} ${GITHUB_USERNAME} <${GITHUB_EMAIL}> 0.1.0.0
- Initial RPM release
EOF
```
заполняем файл данными
```sh
$ cat > CPackConfig.cmake <<EOF
include(InstallRequiredSystemLibraries)
EOF
```
заполняем файл данными
```sh
$ cat >> CPackConfig.cmake <<EOF
set(CPACK_PACKAGE_CONTACT ${GITHUB_EMAIL})
set(CPACK_PACKAGE_VERSION_MAJOR \${PRINT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR \${PRINT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH \${PRINT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_TWEAK \${PRINT_VERSION_TWEAK})
set(CPACK_PACKAGE_VERSION \${PRINT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_FILE \${CMAKE_CURRENT_SOURCE_DIR}/DESCRIPTION)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "static C++ library for printing")
EOF
```
заполняем файл данными
```sh
$ cat >> CPackConfig.cmake <<EOF

set(CPACK_RESOURCE_FILE_LICENSE \${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set(CPACK_RESOURCE_FILE_README \${CMAKE_CURRENT_SOURCE_DIR}/README.md)
EOF
```
заполняем файл данными
```sh
$ cat >> CPackConfig.cmake <<EOF

set(CPACK_RPM_PACKAGE_NAME "print-devel")
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "print")
set(CPACK_RPM_CHANGELOG_FILE \${CMAKE_CURRENT_SOURCE_DIR}/ChangeLog.md)
set(CPACK_RPM_PACKAGE_RELEASE 1)
EOF
```
заполняем файл данными
```sh
$ cat >> CPackConfig.cmake <<EOF

set(CPACK_DEBIAN_PACKAGE_NAME "libprint-dev")
set(CPACK_DEBIAN_PACKAGE_PREDEPENDS "cmake >= 3.0")
set(CPACK_DEBIAN_PACKAGE_RELEASE 1)
EOF
```
заполняем файл данными
```sh
$ cat >> CPackConfig.cmake <<EOF

include(CPack)
EOF
```


редактируем и заоплняем данными симэйк
```sh
$ cat >> CMakeLists.txt <<EOF

include(CPackConfig.cmake)
EOF
```
изменение README.md 
```sh
$ gsed -i 's/lab05/lab06/g' README.md
```
1 - фиксируем изменения 2 - оммитим 3 -
```sh
$ git add .
$ git commit -m"added cpack config"
$ git tag v0.1.0.0
$ git push origin master --tags
```
авторизация в Travis CI 
```sh
$ travis login --auto
$ travis enable
```
сборка и компиляция через CMake. Создание пакета через CPack
```sh
$ cmake -H. -B_build
$ cmake --build _build
$ cd _build
$ cpack -G "TGZ"
$ cd ..
```
сборка и создание пакета через CMake
```sh
$ cmake -H. -B_build -DCPACK_GENERATOR="TGZ"
$ cmake --build _build --target package
```
перемещение собранного пакета
```sh
$ mkdir artifacts
$ mv _build/*.tar.gz artifacts
$ tree artifacts
```


## Homework

После того, как вы настроили взаимодействие с системой непрерывной интеграции,</br>
обеспечив автоматическую сборку и тестирование ваших изменений, стоит задуматься</br>
о создание пакетов для измениний, которые помечаются тэгами (см. вкладку [releases](https://github.com/tp-labs/lab06/releases)).</br>
Пакет должен содержать приложение _solver_ из [предыдущего задания](https://github.com/tp-labs/lab03#задание-1)
Таким образом, каждый новый релиз будет состоять из следующих компонентов:
- архивы с файлами исходного кода (`.tar.gz`, `.zip`)
- пакеты с бинарным файлом _solver_ (`.deb`, `.rpm`, `.msi`, `.dmg`)

В качестве подсказки:
```sh
$ cat .travis.yml
os: osx
script:
...
- cpack -G DragNDrop # dmg

$ cat .travis.yml
os: linux
script:
...
- cpack -G DEB # deb

$ cat .travis.yml
os: linux
addons:
  apt:
    packages:
    - rpm
script:
...
- cpack -G RPM # rpm

$ cat appveyor.yml
platform:
- x86
- x64
build_script:
...
- cpack -G WIX # msi
```

Для этого нужно добавить ветвление в конфигурационные файлы для **CI** со следующей логикой:</br>
если **commit** помечен тэгом, то необходимо собрать пакеты (`DEB, RPM, WIX, DragNDrop, ...`) </br>
и разместить их на сервисе **GitHub**. (см. пример для [Travi CI](https://docs.travis-ci.com/user/deployment/releases))</br>

Текст файла `CPackConfig.cmake`:
```sh
$ cat > CPackConfig.cmake <<EOF
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_CONTACT ${GITHUB_EMAIL})
set(CPACK_PACKAGE_VERSION_MAJOR \${SOLVER_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR \${SOLVER_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH \${SOLVER_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_TWEAK \${SOLVER_VERSION_TWEAK})
set(CPACK_PACKAGE_VERSION \${SOLVER_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_FILE \${CMAKE_CURRENT_SOURCE_DIR}/DESCRIPTION)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "solver app")

set(CPACK_RPM_PACKAGE_NAME "solver")
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "solver")
set(CPACK_RPM_CHANGELOG_FILE \${CMAKE_CURRENT_SOURCE_DIR}/CHANGELOG.md)
set(CPACK_RPM_PACKAGE_RELEASE 1)

set(CPACK_SOURCE_PACKAGE_FILE_NAME "solver-\${SOLVER_VERSION}")
set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")

set(CPACK_DEBIAN_PACKAGE_NAME "solver")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "cmake >= 3.0")
set(CPACK_DEBIAN_PACKAGE_RELEASE 1)

if (CMAKE_INSTALL_PREFIX)
    set(CPACK_OUTPUT_FILE_PREFIX \${CMAKE_INSTALL_PREFIX}/packages)
else()
    set(CPACK_OUTPUT_FILE_PREFIX \${CMAKE_BINARY_DIR}/packages)
endif(CMAKE_INSTALL_PREFIX)

include(CPack)
EOF
```
CMakeLists.txt в корне репозитория:
```sh
$ cat CMakeLists.txt
cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDART 11)
set(CMAKE_CXX_STANDART_REQUIRED ON)

project(solver)

set(SOLVER_VERSION_MAJOR 0)
set(SOLVER_VERSION_MINOR 1)
set(SOLVER_VERSION_PATCH 0)
set(SOLVER_VERSION_TWEAK 0)
set(SOLVER_VERSION
    ${SOLVER_VERSION_MAJOR}.${SOLVER_VERSION_MINOR}.${SOLVER_VERSION_PATCH}.${SOLVER_VERSION_TWEAK})
set(SOLVER_VERSION_STRING "v${SOLVER_VERSION}")

option(INSTALL_FORMATTER "Install libformatter" OFF)
option(INSTALL_FORMATTER_EX "Install libformatter_ex" OFF)
option(INSTALL_HELLOWORLD "Install hello_world" OFF)
option(INSTALL_LIBSOLVER "Install libsolver" OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/hello_world_application)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/solver_application)

include(CPackConfig.cmake)
```

CMakeLists.txt в директории solver_application/   :
```sh
$ cat solver_application/CMakeLists.txt
cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDART 11)
set(CMAKE_CXX_STANDART_REQUIRED ON)

include(${CMAKE_CURRENT_LIST_DIR}/../formatter_ex_lib/CMakeLists.txt)

# specify rule for solver_lib

add_library(libsolver STATIC ${CMAKE_CURRENT_LIST_DIR}/../solver_lib/solver.cpp)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../solver_lib)


add_executable(solver ${CMAKE_CURRENT_LIST_DIR}/equation.cpp)

target_link_libraries(solver formatter_ex libsolver)

if(INSTALL_LIBSOLVER)
    install(TARGETS libsolver 
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
    )
endif(INSTALL_LIBSOLVER)

if (WIN32)
    install(TARGETS solver
        RUNTIME DESTINATION Release
    )
else()
    install(TARGETS solver 
        RUNTIME DESTINATION bin
    )
endif()
```

Текст файла travis.yml
```sh
os:
    - linux
    - osx

language: cpp
compiler:
    - clang
    - gcc

git:
    depth: 1

tags: true

sudo: true

addons:
    apt:
        - cmake
        - cmake-data
        - rpm

script:
    - cmake -H. -Bbuild -DCMAKE_INSTALL_PREFIX=install
    - cmake --build build/
    - cd build/
    - cpack --config CPackSourceConfig.cmake
    - if [ "${TRAVIS_OS_NAME}" = "osx" ]; then cpack -G DragNDrop; fi
    - if [ "${TRAVIS_OS_NAME}" = "linux" ]; then cpack -G RPM; cpack -G DEB; fi
    - cd ..

deploy:
    provider: releases
    api_key: 3f25bd85b48688d5d6ce7e2516140abb29ab06f2
    file_glob: true
    file:
        - "install/packages/*.deb"
        - "install/packages/*.rpm"
        - "install/packages/*.dmg"
        - "install/packages/*.tar.gz"
        - "install/packages/*.zip"
    skip_cleanup: true
    on:
        tags: true
```

Отредактированный .appveyor.yml:
```sh
image: Visual Studio 2015

platform:
    - x86
    - x64

configuration: Release
build:
    parallel: true

build_script:
    - cmake -H. -Bbuild -DCMAKE_INSTALL_PREFIX=install
    - cmake --build build
    - cmake --build build --target install
    - cmake -H. -Bbuild -DCPACK_GENERATOR=WIX 
    - cmake --build build --target package

artifacts:
    - path: install\packages\*.msi
      name: solver

deploy:
    description: 'Some minor fixes'
    provider: GitHub
    auth_token:
        secure: nrOKU0Jm6cqrVLiZjit9dgn/S0HbdJGYXTKq50Jk0ekG8KaUPOhP6oobOGNt7+Dr
    draft: false
    prerelease: false
    on:
        APPVEYOR_REPO_TAG: true
```
## Links

- [DMG](https://cmake.org/cmake/help/latest/module/CPackDMG.html)
- [DEB](https://cmake.org/cmake/help/latest/module/CPackDeb.html)
- [RPM](https://cmake.org/cmake/help/latest/module/CPackRPM.html)
- [NSIS](https://cmake.org/cmake/help/latest/module/CPackNSIS.html)

```
Copyright (c) 2015-2021 The ISC Authors
```
