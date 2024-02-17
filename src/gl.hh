#ifndef GL_HH
#define GL_HH

#include "u.hh"

namespace gl {
    extern "C" {

        void log(const char* ptr);
        u32 get_width();
        u32 get_height();

        void clear_color(float r, float g, float b, float a);
        void clear(u32 mask);

        u32 create_buffer();
        void bind_buffer(u32 type, u32 buffer);
        void buffer_data(u32 type, f32* data, usize length, u32 hint);

        u32 create_shader(u32 type);
        void shader_source(u32 shader, const char* path);
        void compile_shader(u32 shader);

        u32 create_program();
        void attach_shader(u32 program, u32 shader);
        void link_program(u32 program);
        i32 get_attrib_location(u32 program, const char* attrib);
        void use_program(u32 program);

        void viewport(u32 x, u32 y, u32 w, u32 h);

        void enable_vertex_attrib_array(i32 location);
        void vertex_attrib_pointer(i32 location, usize size, u32 type, u8 normalized, usize stride, usize offset);
        void draw_arrays(u32 mode, usize first, usize count);

    } 

    struct buffer {
        u32 id;
        u32 type;

        enum { ARRAY = 0x8892, ELEMENT_ARRAY };

        static auto create(u32 type) -> buffer;
        auto bind() -> void;
        auto set_data(f32* data, usize length, u32 hint) -> void;
    };

    struct shader {
        u32 id;

        enum { FRAGMENT = 0x8B30, VERTEX };

        static auto create(u32 type) -> shader;
        auto set_source(const char* path) -> void;
        auto compile() -> void;
    };

    struct program {
        u32 id;

        static auto create() -> program;
        auto attach(shader& s) -> void;
        auto link() -> void;
        auto use() -> void;
        auto attrib_location(const char* attrib) -> i32;
    };

    // https://developer.mozilla.org/en-US/docs/Web/API/WebGL_API/Constants

    enum {
        DEPTH_BUFFER_BIT = 0x00000100,
        STENCIL_BUFFER_BIT = 0x00000400,
        COLOR_BUFFER_BIT = 0x00004000,
    };

    enum {
        STATIC_DRAW = 0x88E4,
        STREAM_DRAW = 0x88E0,
        DYNAMIC_DRAW = 0x88E8,
    };

    enum {
        BYTE = 0x1400,
        UNSIGNED_BYTE,
        SHORT,
        UNSIGNED_SHORT,
        INT,
        UNSIGNED_INT,
        FLOAT
    };

    enum {
        POINTS = 0x0000,
        LINES,
        LINE_LOOP,
        LINE_STRIP,
        TRIANGLES,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
    };

}

#endif
