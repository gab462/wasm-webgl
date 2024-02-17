#include "gl.hh"
#include "u.hh"

namespace gl {

    auto buffer::create(u32 type) -> buffer {
        u32 buf = create_buffer();
        return buffer{ buf, type };
    }

    auto buffer::bind() -> void {
        bind_buffer(this->type, this->id);
    }

    auto buffer::set_data(f32* data, usize length, u32 hint) -> void {
        buffer_data(this->type, data, length, hint);
    }

    auto shader::create(u32 type) -> shader {
        return shader{ create_shader(type) };
    }

    auto shader::set_source(const char* path) -> void {
        shader_source(this->id, path);
    }

    auto shader::compile() -> void {
        compile_shader(this->id);
    }

    auto program::create() -> program {
        return program{ create_program() };
    }

    auto program::attach(shader& s) -> void {
        attach_shader(this->id, s.id);
    }

    auto program::link() -> void {
        link_program(this->id);
    }

    auto program::use() -> void {
        use_program(this->id);
    }

    auto program::attrib_location(const char* attrib) -> i32 {
        return get_attrib_location(this->id, attrib);
    }

}
