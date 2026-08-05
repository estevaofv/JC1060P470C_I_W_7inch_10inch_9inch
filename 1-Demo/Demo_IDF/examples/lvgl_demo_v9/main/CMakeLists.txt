set(LV_DEMO_DIR ../managed_components/lvgl__lvgl/demos)
file(GLOB_RECURSE LV_DEMOS_SOURCES ${LV_DEMO_DIR}/*.c)

idf_component_register(
    SRCS main.c ${LV_DEMOS_SOURCES}
    INCLUDE_DIRS . ${LV_DEMO_DIR})

idf_component_get_property(LVGL_LIB lvgl__lvgl COMPONENT_LIB)
target_compile_options(
    ${LVGL_LIB}
    PRIVATE
        -DLV_LVGL_H_INCLUDE_SIMPLE
        -DLV_USE_DEMO_MUSIC
        # GCC 15 (ESP-IDF v6) rejects LVGL's LV_ATTRIBUTE_FAST_MEM=IRAM_ATTR on some
        # static draw helpers: "ignoring attribute section('.iram1.N') because it
        # conflicts with previous section('.iram1.M')". GCC just drops the IRAM
        # placement for those functions, so this is a placement hint, not a
        # correctness issue. Downgrade to a warning to keep
        # CONFIG_LV_ATTRIBUTE_FAST_MEM_USE_IRAM=y working for the rest.
        -Wno-error=attributes
)
