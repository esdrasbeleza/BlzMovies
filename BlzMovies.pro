# Add files and directories to ship with the application 
# by adapting the examples below.
# file1.source = myfile
# dir1.source = mydir
DEPLOYMENTFOLDERS = # file1 dir1

symbian:TARGET.UID3 = 0xE346E126

# Smart Installer package's UID
# This UID is from the protected range 
# and therefore the package will fail to install if self-signed
# By default qmake uses the unprotected range value if unprotected UID is defined for the application
# and 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment
# the following lines and add the respective components to the 
# MOBILITY variable. 
# CONFIG += mobility
# MOBILITY +=

QT += network \
      xml \
      xmlpatterns
SOURCES += main.cpp mainwindow.cpp \
    movie.cpp \
    randommovie.cpp \
    searchmovie.cpp \
    searchresultlistitem.cpp \
    searchwindow.cpp
HEADERS += mainwindow.h \
    movie.h \
    randommovie.h \
    searchmovie.h \
    searchresultlistitem.h \
    searchwindow.h
FORMS += mainwindow.ui \
    result_item.ui \
    search_results.ui \
    details.ui \
    searchwindow.ui

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

DEFINES += THEMOVIEDB_KEY=\\\"8b0246355e819cf5dc82d9c1c4b27227\\\"

OTHER_FILES +=
