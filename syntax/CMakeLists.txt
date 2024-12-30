# Define the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Define the source files for the syntax highlighting files
set(SYNTAX_SRC_FILES
    asm.nanorc
    autoconf.nanorc
    awk.nanorc
    changelog.nanorc
    cmake.nanorc
    c.nanorc
    css.nanorc
    default.nanorc
    elisp.nanorc
    email.nanorc
    go.nanorc
    groff.nanorc
    guile.nanorc
    html.nanorc
    java.nanorc
    javascript.nanorc
    json.nanorc
    lua.nanorc
    makefile.nanorc
    man.nanorc
    markdown.nanorc
    nanohelp.nanorc
    nanorc.nanorc
    nftables.nanorc
    objc.nanorc
    ocaml.nanorc
    patch.nanorc
    perl.nanorc
    php.nanorc
    po.nanorc
    python.nanorc
    ruby.nanorc
    rust.nanorc
    sh.nanorc
    sql.nanorc
    tcl.nanorc
    tex.nanorc
    texinfo.nanorc
    xml.nanorc
    yaml.nanorc
    extra/ada.nanorc
    extra/fortran.nanorc
    extra/haskell.nanorc
    extra/povray.nanorc
    extra/spec.nanorc
)

# Add custom targets for installing syntax highlighting files
install(FILES ${SYNTAX_SRC_FILES} DESTINATION ${CMAKE_INSTALL_DATADIR}/nano)

# Set required dependencies and commands for installing syntax highlighting files
add_custom_target(install-syntax ALL
    DEPENDS ${SYNTAX_SRC_FILES}
    COMMAND ${CMAKE_COMMAND} -E copy ${SYNTAX_SRC_FILES} ${CMAKE_INSTALL_DATADIR}/nano
)
