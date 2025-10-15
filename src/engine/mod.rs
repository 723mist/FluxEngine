extern crate glfw;
extern crate gl;

use glfw::{Action, Context, Key, WindowEvent};
use gl::types::*;

pub fn window(title: &str, width: u32, height: u32) {

    use glfw::fail_on_errors;
    let mut glfw = glfw::init(fail_on_errors!()).unwrap();

    let (mut window, _events) = glfw.create_window(width, height, title, glfw::WindowMode::Windowed).expect("Failed to create GLFW window.");

    window.make_current();
    window.set_key_polling(true);

    //gl::load_with(|symbol| window.get_proc_address(symbol) as *const _);

    while !window.should_close() {
        window.swap_buffers();
        /*unsafe {
            gl::ClearColor(1.0, 1.0, 1.0, 1.0);
        }*/
        glfw.poll_events();
        /*for (_, event) in glfw::flush_messages(&events) {
            println!("{:?}", event);
            match event {
                glfw::WindowEvent::Key(Key::Escape, _, Action::Press, _) => {
                    window.set_should_close(true)
                },
                _ => {},
            }
        }*/
    }

}
