#include "u.hh"
#include "gl.hh"

f32 triangle[] = {
    0.f, 0.5,
    -0.5f, -0.5f,
    0.5f, -0.5f
};

namespace state {
    gl::buffer buffer;
    gl::shader vs;
    gl::shader fs;
    gl::program program;
    u32 vertex_position;
}

char vertex_shader[] =
/* #embed "vertex.glsl" */
"#version 300 es\n"
"precision mediump float;\n"
"in vec2 vertex_position;\n"
"void main() {\n"
"     gl_Position = vec4(vertex_position, 0.0, 1.0);\n"
"}\n";

char fragment_shader[] =
/* #embed "fragment.glsl" */
"#version 300 es\n"
"precision mediump float;\n"
"out vec4 color;\n"
"void main() {\n"
"     color = vec4(0.3, 0.3, 0.8, 1.0);\n"
"}\n";

extern "C" {

    auto init() -> void {
        gl::log("Initialized");

        using namespace state;

        buffer = gl::buffer::create(gl::buffer::ARRAY);
        buffer.bind();
        buffer.set_data(triangle, 6, gl::STATIC_DRAW);

        vs = gl::shader::create(gl::shader::VERTEX);
        vs.set_source(vertex_shader);
        vs.compile();

        fs = gl::shader::create(gl::shader::FRAGMENT);
        fs.set_source(fragment_shader);
        fs.compile();

        program = gl::program::create();
        program.attach(state::vs);
        program.attach(state::fs);
        program.link();

        vertex_position = state::program.attrib_location("vertex_position");
    }

    auto update(int timestamp) -> void {
        (void) timestamp;
    }

    auto render() -> void {
        gl::clear_color(0.8f, 0.3f, 0.3f, 1.f);
        gl::clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

        gl::viewport(0, 0, gl::get_width(), gl::get_height());

        state::program.use();
        gl::enable_vertex_attrib_array(state::vertex_position);

        state::buffer.bind();
        gl::vertex_attrib_pointer(state::vertex_position, 2, gl::FLOAT, 0, 2 * sizeof(f32), 0);

        gl::draw_arrays(gl::TRIANGLES, 0, 3);
    }

    auto key_down(char c) -> void {
        (void) c;
    }

    auto key_up(char c) -> void {
        (void) c;
    }

    auto mouse_down(i32 x, i32 y) -> void {
        (void) x;
        (void) y;
    }

    auto mouse_up(i32 x, i32 y) -> void {
        (void) x;
        (void) y;
    }

}
