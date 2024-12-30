# CMake configuration for localization files

# Define the source files for the localization files
set(LOCALE_FILES
    bg.po
    ca.po
    cs.po
    da.po
    de.po
    eo.po
    es.po
    eu.po
    fi.po
    fr.po
    ga.po
    gl.po
    hr.po
    hu.po
    id.po
    is.po
    it.po
    ja.po
    ka.po
    ko.po
    ms.po
    nb.po
    nl.po
    pl.po
    pt.po
    pt_BR.po
    ro.po
    ru.po
    sk.po
    sl.po
    sq.po
    sr.po
    sv.po
    tr.po
    uk.po
    vi.po
    zh_CN.po
    zh_TW.po
)

# Add custom targets for generating and installing localization files
add_custom_target(generate_locales ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/locale
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/bg.po ${CMAKE_BINARY_DIR}/locale/bg.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/ca.po ${CMAKE_BINARY_DIR}/locale/ca.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/cs.po ${CMAKE_BINARY_DIR}/locale/cs.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/da.po ${CMAKE_BINARY_DIR}/locale/da.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/de.po ${CMAKE_BINARY_DIR}/locale/de.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/eo.po ${CMAKE_BINARY_DIR}/locale/eo.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/es.po ${CMAKE_BINARY_DIR}/locale/es.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/eu.po ${CMAKE_BINARY_DIR}/locale/eu.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/fi.po ${CMAKE_BINARY_DIR}/locale/fi.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/fr.po ${CMAKE_BINARY_DIR}/locale/fr.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/ga.po ${CMAKE_BINARY_DIR}/locale/ga.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/gl.po ${CMAKE_BINARY_DIR}/locale/gl.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/hr.po ${CMAKE_BINARY_DIR}/locale/hr.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/hu.po ${CMAKE_BINARY_DIR}/locale/hu.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/id.po ${CMAKE_BINARY_DIR}/locale/id.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/is.po ${CMAKE_BINARY_DIR}/locale/is.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/it.po ${CMAKE_BINARY_DIR}/locale/it.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/ja.po ${CMAKE_BINARY_DIR}/locale/ja.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/ka.po ${CMAKE_BINARY_DIR}/locale/ka.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/ko.po ${CMAKE_BINARY_DIR}/locale/ko.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/ms.po ${CMAKE_BINARY_DIR}/locale/ms.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/nb.po ${CMAKE_BINARY_DIR}/locale/nb.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/nl.po ${CMAKE_BINARY_DIR}/locale/nl.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/pl.po ${CMAKE_BINARY_DIR}/locale/pl.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/pt.po ${CMAKE_BINARY_DIR}/locale/pt.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/pt_BR.po ${CMAKE_BINARY_DIR}/locale/pt_BR.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/ro.po ${CMAKE_BINARY_DIR}/locale/ro.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/ru.po ${CMAKE_BINARY_DIR}/locale/ru.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/sk.po ${CMAKE_BINARY_DIR}/locale/sk.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/sl.po ${CMAKE_BINARY_DIR}/locale/sl.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/sq.po ${CMAKE_BINARY_DIR}/locale/sq.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/sr.po ${CMAKE_BINARY_DIR}/locale/sr.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/sv.po ${CMAKE_BINARY_DIR}/locale/sv.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/tr.po ${CMAKE_BINARY_DIR}/locale/tr.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/uk.po ${CMAKE_BINARY_DIR}/locale/uk.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/vi.po ${CMAKE_BINARY_DIR}/locale/vi.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/zh_CN.po ${CMAKE_BINARY_DIR}/locale/zh_CN.po
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/zh_TW.po ${CMAKE_BINARY_DIR}/locale/zh_TW.po
)

install(DIRECTORY ${CMAKE_BINARY_DIR}/locale/ DESTINATION ${CMAKE_INSTALL_PREFIX}/share/locale)
