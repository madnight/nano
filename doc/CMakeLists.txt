# Define the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Define the source files for the documentation
set(DOC_SRC_FILES
    nano.1
    rnano.1
    nanorc.5
    nano.texi
)

# Add custom targets for generating man pages and HTML documentation
add_custom_target(man_pages ALL
    COMMAND groff -t -mandoc -Thtml < nano.1 > nano.1.html
    COMMAND groff -t -mandoc -Thtml < rnano.1 > rnano.1.html
    COMMAND groff -t -mandoc -Thtml < nanorc.5 > nanorc.5.html
    DEPENDS ${DOC_SRC_FILES}
)

add_custom_target(html_docs ALL
    COMMAND makeinfo --html --no-split nano.texi
    DEPENDS nano.texi
)

# Set required dependencies and commands for generating documentation
add_dependencies(html_docs man_pages)
