extern crate gl;
extern crate glfw;
extern crate gl_loader;

use gl::types::*;
use glfw::{Context};
use std::mem::size_of_val;
use std::ffi::CString;

const VERTEX_SHADER_SOURCE: &str = r#"
    #version 330 core
    layout (location = 0) in vec3 aPos;    // позиция вершины
    layout (location = 1) in vec3 aColor;  // цвет вершины

    out vec3 ourColor; // передаём во фрагментный шейдер

    void main()
    {
        gl_Position = vec4(aPos, 1.0);
        ourColor = aColor; // просто передаём цвет дальше
    }
"#;

const FRAGMENT_SHADER_SOURCE: &str = r#"
    #version 330 core
    out vec4 FragColor;

    in vec3 ourColor; // принимаем цвет из vertex shader

    void main()
    {
        FragColor = vec4(ourColor, 1.0); // рисуем этим цветом
    }
"#;


pub fn window(title: &str, width: u32, height: u32) {

    use glfw::fail_on_errors;
    let mut glfw = glfw::init(fail_on_errors!()).unwrap();

    let (mut window, _events) = glfw.create_window(width, height, title, glfw::WindowMode::Windowed).expect("Failed to create GLFW window");

    window.make_current();
    window.set_key_polling(true);

    gl_loader::init_gl();

    gl::load_with(|symbol| gl_loader::get_proc_address(symbol) as *const _);

    let vertices: Vec<f32> = vec![
        0.0,  0.5, 0.0,  1.0, 0.0, 0.0,
        -0.5, -0.5, 0.0,  0.0, 1.0, 0.0,
        0.5, -0.5, 0.0,  0.0, 0.0, 1.0,
    ];

    let mut vbo: u32 = 0;
    let mut vao: u32 = 0;

    let vertex_shader: u32;
    let fragment_shader: u32;
    let shader_program: u32;

    //SHADER(VBO)
    unsafe {
        //Shaders
        vertex_shader = gl::CreateShader(gl::VERTEX_SHADER);
        fragment_shader = gl::CreateShader(gl::FRAGMENT_SHADER);
        shader_program = gl::CreateProgram();

        let vertex_source = CString::new(VERTEX_SHADER_SOURCE).unwrap();
        let fragment_source = CString::new(FRAGMENT_SHADER_SOURCE).unwrap();

        //Shader source
        gl::ShaderSource(vertex_shader, 1, &vertex_source.as_ptr(), std::ptr::null());
        gl::ShaderSource(fragment_shader, 1, &fragment_source.as_ptr(), std::ptr::null());

        //Compile shader
        gl::CompileShader(vertex_shader);
        gl::CompileShader(fragment_shader);

        //Attach shader
        gl::AttachShader(shader_program, vertex_shader);
        gl::AttachShader(shader_program, fragment_shader);

        //Link program
        gl::LinkProgram(shader_program);

        //Delete shader
        gl::DeleteShader(vertex_shader);
        gl::DeleteShader(fragment_shader);

        //Use program shader
        gl::UseProgram(shader_program);

        //Gen buffers
        //gl::GenBuffers(1, &mut vbo);

        //Bind buffer
        //gl::BindBuffer(gl::ARRAY_BUFFER, vbo);

        //Bufer data
        //gl::BufferData(gl::ARRAY_BUFFER, size_of_val(vertices.as_slice()) as isize, vertices.as_ptr() as *const GLvoid, gl::STATIC_DRAW);

        //Vertex attrib pointer
        //gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE, (6 * std::mem::size_of::<f32>()) as i32, std::ptr::null());

        //Enable vertex attrib array
        //gl::EnableVertexAttribArray(1);
    }

    //SHADER(VAO)
    unsafe {
        //Gen vertex arrays
        gl::GenVertexArrays(1, &mut vao);
        //Gen buffers
        gl::GenBuffers(1, &mut vbo);

        //Bind vertex array
        gl::BindVertexArray(vao);

        //Bind buffer
        gl::BindBuffer(gl::ARRAY_BUFFER, vbo);

        //Buffer data
        gl::BufferData(gl::ARRAY_BUFFER, size_of_val(vertices.as_slice()) as isize, vertices.as_ptr() as *const GLvoid, gl::STATIC_DRAW);

        // Позиция
        gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE, 6 * 4, std::ptr::null());
        gl::EnableVertexAttribArray(0);

        // Цвет
        gl::VertexAttribPointer(1, 3, gl::FLOAT, gl::FALSE, 6 * 4, (3 * 4) as *const _);
        gl::EnableVertexAttribArray(1);
    }

    //Main loop
    while !window.should_close() {
        window.swap_buffers();
        unsafe {
            gl::ClearColor(0.2, 0.3, 0.3, 1.0);
            gl::Clear(gl::COLOR_BUFFER_BIT);

            gl::BindVertexArray(vao);

            gl::DrawArrays(gl::TRIANGLES, 0, 3);
        }
        glfw.poll_events();
    }
    gl_loader::end_gl();
}