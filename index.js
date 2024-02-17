async function main() {
    let app = document.getElementById("app");
    let gl = app.getContext("webgl2");
    let glObjs = [];		// Interface to js objects from C

    let buffer = null;

    function cstr(ptr) {
        let mem = new Uint8Array(buffer);
        let len = 0;
        while (mem[ptr + len] != 0) {
            len++;
        }

        return new TextDecoder().decode(new Uint8Array(buffer, ptr, len));
    }

    let wasm = await WebAssembly.instantiateStreaming(fetch('index.wasm'), {
        env: {
            log: (ptr) => console.log(cstr(ptr)),
            get_width: () => app.width,
            get_height: () => app.height,
            clear_color: (r, g, b, a) => gl.clearColor(r, g, b, a),
            clear: (mask) => gl.clear(mask),
            create_buffer: () => glObjs.push(gl.createBuffer()) - 1,
            bind_buffer: (type, handle) => gl.bindBuffer(type, glObjs[handle]),
            buffer_data: (type, data, len, hint) => gl.bufferData(type, new Float32Array(buffer, data, len), hint),
            create_shader: (type) => glObjs.push(gl.createShader(type)) - 1,
            shader_source: (handle, code) => gl.shaderSource(glObjs[handle], cstr(code)),
            compile_shader: (handle) => gl.compileShader(glObjs[handle]),
            create_program: () => glObjs.push(gl.createProgram()) - 1,
            attach_shader: (program_handle, shader_handle) => gl.attachShader(glObjs[program_handle], glObjs[shader_handle]),
            link_program: (handle) => gl.linkProgram(glObjs[handle]),
            get_attrib_location: (handle, attrib) => gl.getAttribLocation(glObjs[handle], cstr(attrib)),
            viewport: (x, y, w, h) => gl.viewport(x, y, w, h),
            use_program: (handle) => gl.useProgram(glObjs[handle]),
            enable_vertex_attrib_array: (location) => gl.enableVertexAttribArray(location),
            vertex_attrib_pointer: (index, size, type, normalized, stride, offset) => gl.vertexAttribPointer(index, size, type, normalized, stride, offset),
            draw_arrays: (mode, first, count) => gl.drawArrays(mode, first, count),
        }
    });

    let c = wasm.instance.exports;
    buffer = c.memory.buffer;

    c.init();

    let loop = timestamp => {
        c.update(timestamp);
        c.render();

        window.requestAnimationFrame(loop);
    };

    Object.entries({
        keydown: e => c.key_down(e.key.charCodeAt()),
        keyup: e => c.key_up(e.key.charCodeAt()),
        mousedown: e => c.mouse_down(e.x, e.y),
        mouseup: e => c.mouse_up(e.x, e.y)
    }).forEach(([event, fn]) => {
        document.addEventListener(event, fn);
    });

    window.requestAnimationFrame(loop);
}

main();
