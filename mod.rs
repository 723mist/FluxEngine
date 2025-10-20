extern crate glfw;
extern crate gl;
extern crate gl_loader;

//use std::ffi::c_char;
use gl::types::{/*GLchar,*/ GLvoid};
use std::mem::size_of_val;
//use std::ptr;
use glfw::{/*Action,*/ Context/*, Key, WindowEvent*/};

const VERTEX_SHADER_SOURCE: &str = r#"
    #version 330 core
    layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
    layout (location = 1) in vec3 aColor; // the color variable has attribute position 1

    out vec3 ourColor; // output a color to the fragment shader

    void main()
    {
        gl_Position = vec4(aPos, 1.0);
        ourColor = aColor; // set ourColor to the input color we got from the vertex data
    }
"#;

/*const FRAGMENT_SHADER_SOURCE: &str = r#"
    #version 330 core
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(1.0f, 0.0f, 0.5f, 1.0f);
    }
"#;*/

const FRAGMENT_SHADER_SOURCE: &str = r#"
    #version 330 core
    out vec4 FragColor;
    in vec3 ourColor;

    void main()
    {
        FragColor = vec4(ourColor, 1.0);
    }
"#;

pub fn window(title: &str, width: u32, height: u32) {

    use glfw::fail_on_errors;
    let mut glfw = glfw::init(fail_on_errors!()).unwrap();

    let (mut window, _events) = glfw.create_window(width, height, title, glfw::WindowMode::Windowed).expect("Failed to create GLFW window.");

    window.make_current();
    window.set_key_polling(true);

    gl_loader::init_gl();

    gl::load_with(|symbol| gl_loader::get_proc_address(symbol) as *const _);

    /*let vertices: Vec<f32> = vec![
        0.5,  0.5, 0.0,  // top right
        0.5, -0.5, 0.0,  // bottom right
        -0.5,  0.5, 0.0, // top left

        0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0,
        -0.5,  0.5, 0.0
    ];*/

    /*let vertices: Vec<f32> = vec![
        -0.5, -0.5, 0.0,
        0.5, -0.5, 0.0,
        0.0,  0.35, 0.0
    ];*/

    let vertices: Vec<f32> = vec![
        0.5, -0.5, 0.0,  1.0, 0.0, 0.0,   // bottom right
        -0.5, -0.5, 0.0,  0.0, 1.0, 0.0,   // bottom left
        0.0,  0.5, 0.0,  0.0, 0.0, 1.0   // top

    ];

    let mut vbo: u32 = 0;

    let vao: u32 = 0;

    let vertex_shader: u32;

    let fragment_shader: u32;

    let shader_program: u32;

    unsafe {

        gl::GenBuffers(1, &mut vbo);
        gl::BindVertexArray(vao);

        gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
        gl::BufferData(gl::ARRAY_BUFFER, size_of_val(vertices.as_slice()) as isize, vertices.as_ptr() as *const GLvoid, gl::STATIC_DRAW);

        gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE, (6 * std::mem::size_of::<f32>()) as i32, std::ptr::null());
        gl::EnableVertexAttribArray(0);

        // Атрибут цветов (location = 1)
        gl::VertexAttribPointer(1, 3, gl::FLOAT, gl::FALSE, (6 * std::mem::size_of::<f32>()) as i32, (3 * std::mem::size_of::<f32>()) as *const GLvoid);
        gl::EnableVertexAttribArray(1);

        vertex_shader = gl::CreateShader(gl::VERTEX_SHADER);
        fragment_shader = gl::CreateShader(gl::FRAGMENT_SHADER);
        shader_program = gl::CreateProgram();

        //MADE AI REMAKE
        let source_c_str = std::ffi::CString::new(VERTEX_SHADER_SOURCE).unwrap();
        let source_ptr = source_c_str.as_ptr();
        gl::ShaderSource(vertex_shader, 1, &source_ptr, std::ptr::null());

        let source_c_str = std::ffi::CString::new(FRAGMENT_SHADER_SOURCE).unwrap();
        let source_ptr = source_c_str.as_ptr();
        gl::ShaderSource(fragment_shader, 1, &source_ptr, std::ptr::null());
        //REMAKE

        //gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE, 6, std::ptr::null());
        //gl::EnableVertexAttribArray(0);

        gl::AttachShader(shader_program, vertex_shader);
        gl::AttachShader(shader_program, fragment_shader);
        gl::LinkProgram(shader_program);
        gl::EnableVertexAttribArray(0);

        gl::UseProgram(shader_program);
        gl::BindVertexArray(vao);

        //gl::ShaderSource(vertex_shader, 1, VERTEX_SHADER_SOURCE.as_ptr() as *const GLchar, ptr::null());
        gl::CompileShader(vertex_shader);
        gl::CompileShader(fragment_shader);

        gl::DeleteShader(vertex_shader);
    }

    while !window.should_close() {
        window.swap_buffers();
        unsafe {
            gl::Viewport(0, 0, width as i32, height as i32);
            gl::ClearColor(0.2, 0.2, 0.3, 1.0);
            gl::Clear(gl::COLOR_BUFFER_BIT);

            //gl::PolygonMode(gl::FRONT_AND_BACK, gl::LINE);

            gl::DrawArrays(gl::TRIANGLES, 0, 3);
        }
        glfw.poll_events();
    }
    gl_loader::end_gl();
}
