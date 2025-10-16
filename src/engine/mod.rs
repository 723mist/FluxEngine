extern crate glfw;
extern crate gl;
extern crate gl_loader;

use glfw::{Action, Context, Key, /*WindowEvent*/};
//use gl::types::*;

pub fn window(title: &str, width: u32, height: u32) {

    use glfw::fail_on_errors;
    let mut glfw = glfw::init(fail_on_errors!()).unwrap();

    let (mut window, events) = glfw.create_window(width, height, title, glfw::WindowMode::Windowed).expect("Failed to create GLFW window.");

    window.make_current();
    window.set_key_polling(true);

    //gl::load_with(|symbol| window.get_proc_address(symbol) as *const _);

    gl_loader::init_gl();

    gl::load_with(|symbol| gl_loader::get_proc_address(symbol) as *const _);

    while !window.should_close() {
        window.swap_buffers();
        unsafe {
            gl::ClearColor(0.2, 0.2, 0.3, 1.0);
            gl::Clear(gl::COLOR_BUFFER_BIT);
        }
        glfw.poll_events();
        for (_, event) in glfw::flush_messages(&events) {
            println!("{:?}", event);
            match event {
                glfw::WindowEvent::Key(Key::Escape, _, Action::Press, _) => {
                    //window.set_should_close(true)
                    println!("Escape pressed");
                },
                _ => {},
            }
        }
    }
    gl_loader::end_gl();
}
