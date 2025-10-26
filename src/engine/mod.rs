extern crate gl;
extern crate glfw;
extern crate gl_loader;
extern crate image;
extern crate glm;

use gl::types::*;
use glfw::{Context, Key, Action}; //Window
use std::mem::size_of_val;
use std::ffi::CString;
use std::path::{Path}; //PathBuf
//use glm::{vec4, vec3, Mat4};
//use glu_sys::*;

#[allow(unused_imports)]
use image::GenericImageView;

const VERTEX_SHADER_SOURCE: &str = r#"
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;
    layout (location = 2) in vec2 aTexCoord;

    out vec3 ourColor;
    out vec2 TexCoord;

    void main()
    {
        gl_Position = vec4(aPos, 1.0);
        ourColor = aColor;
        TexCoord = aTexCoord;
    }
"#;
const FRAGMENT_SHADER_SOURCE: &str = r#"
    #version 330 core
    out vec4 FragColor;

    in vec3 ourColor;
    in vec2 TexCoord;

    uniform sampler2D ourTexture;

    void main()
    {
        FragColor = texture(ourTexture, TexCoord);
    }
"#;

pub fn window(title: &str, width: u32, height: u32) {

    use glfw::fail_on_errors;
    let mut glfw = glfw::init(fail_on_errors!()).unwrap();

    let (mut window, _events) = glfw.create_window(width, height, title, glfw::WindowMode::Windowed).expect("Failed to create GLFW window");

    let debug_mode: bool = true;

    window.make_current();
    window.set_key_polling(true);

    gl_loader::init_gl();

    gl::load_with(|symbol| gl_loader::get_proc_address(symbol) as *const _);

    let vertices: Vec<f32> = vec![
        0.5,  0.5, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0,
        0.5, -0.5, 0.0,   0.0, 1.0, 0.0,   1.0, 1.0,
        -0.5, -0.5, 0.0,   0.0, 0.0, 1.0,   0.0, 1.0,
        -0.5,  0.5, 0.0,   1.0, 1.0, 0.0,   0.0, 0.0
    ];

    let _tex_coords: Vec<f32> = vec![
        0.0, 0.0,
        1.0, 0.0,
        0.5, 1.0
    ];

    let border_color: Vec<f32> = vec!{ 1.0, 1.0, 0.0, 1.0 };

    let mut vbo: u32 = 0;
    let mut vao: u32 = 0;
    let mut ebo: u32 = 0;

    let indices: Vec<u32> = vec!{
        0, 1, 3,
        1, 2, 3
    };

    //Shaders
    let vertex_shader: u32;
    let fragment_shader: u32;
    let shader_program: u32;

    let mut texture: u32 = 0;

    //Texture path
    //let _texture_path = Path::new(env!("CARGO_MANIFEST_DIR")).join(Self::texture_load);
    let _texture_path = Path::new(env!("CARGO_MANIFEST_DIR")).join("content/defult.jpg");

    //Image + error
    let img = image::open(_texture_path).unwrap_or_else(|e| panic!("Failed to load texture. Error: {}", e));

    //Image type RGBA
    let img_rgba = img.to_rgba8();

    //Image dimensions
    let (width, height) = img_rgba.dimensions();

    //SHADER(VBO)
    unsafe {
        //Shaders
        vertex_shader = gl::CreateShader(gl::VERTEX_SHADER);
        fragment_shader = gl::CreateShader(gl::FRAGMENT_SHADER);
        shader_program = gl::CreateProgram();

        //Vertex and fragment sources
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

        //Vertex attrib pointer
        gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE, 8 * 4, std::ptr::null());
        gl::VertexAttribPointer(1, 3, gl::FLOAT, gl::FALSE, 8 * 4, (3 * 4) as *const _);
        gl::VertexAttribPointer(2, 2, gl::FLOAT, gl::FALSE, 8 * 4, (6 * 4) as *const _);

        //Enable vertex attrib array(color)
        gl::EnableVertexAttribArray(0);
        gl::EnableVertexAttribArray(1);
        gl::EnableVertexAttribArray(2);
    }

    //EBO
    unsafe {
        //Gen buffer(for EBO)
        gl::GenBuffers(1, &mut ebo);

        //Bind buffer
        gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, ebo);

        //Buffer data
        gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, size_of_val(indices.as_slice()) as isize, indices.as_ptr() as *const GLvoid, gl::STATIC_DRAW);
    }

    //Textures
    unsafe {
        //Generate texture
        gl::GenTextures(1, &mut texture);

        //Bind texture
        gl::BindTexture(gl::TEXTURE_2D, texture);

        //Texture parameteri
        gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::MIRRORED_REPEAT as i32);
        gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::MIRRORED_REPEAT as i32);

        //Texture parameterfv
        gl::TexParameterfv(gl::TEXTURE_2D, gl::TEXTURE_BORDER_COLOR, border_color.as_ptr());

        //Texture parameteri
        gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::NEAREST as i32);

        //Texture image 2D
        gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGBA as i32, width as i32, height as i32, 0, gl::RGBA, gl::UNSIGNED_BYTE, img_rgba.as_ptr() as *const GLvoid);

        //Generate mipmap
        gl::GenerateMipmap(gl::TEXTURE_2D);
    }

    //Main loop
    while !window.should_close() {
        window.swap_buffers();
        unsafe {
            gl::ClearColor(0.2, 0.3, 0.3, 1.0);
            gl::Clear(gl::COLOR_BUFFER_BIT);

            gl::BindTexture(gl::TEXTURE_2D, texture);
            gl::BindVertexArray(vao);

            gl::DrawElements(gl::TRIANGLES, 6, gl::UNSIGNED_INT, std::ptr::null());
            //gl::DrawArrays(gl::TRIANGLES, 0, 6); //Old
        }
        glfw.poll_events();
        for (_, event) in glfw::flush_messages(&_events) {
            if debug_mode == true {
                match event {
                    glfw::WindowEvent::Key(Key::Escape, _, Action::Press, _) => {
                        unsafe {
                            static mut WIRFRAME_MODE: bool = false;
                            WIRFRAME_MODE = !WIRFRAME_MODE;

                            if WIRFRAME_MODE {
                                gl::PolygonMode(gl::FRONT_AND_BACK, gl::LINE);
                                println!("Debug mode(WIRFRAME_MODE)");
                            } else {
                                gl::PolygonMode(gl::FRONT_AND_BACK, gl::FILL);
                                println!("Normal mode");
                            }
                        }
                    },
                    _ => {},
                }
            }
        }
    }
    gl_loader::end_gl();
}

