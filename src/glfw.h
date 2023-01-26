JanetFunction *key_callback = NULL;

static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Janet args[4];
    Janet k;
    bool found = false;
    for (unsigned i = 0; i < (sizeof(key_defs) / sizeof(KeyDef)); i++) {
        if (key_defs[i].key == key) {
            k = janet_ckeywordv(key_defs[i].name);
            found = true;
        }
    }

    if (!found) { k = janet_wrap_integer(key); }

    args[0] = k;
    args[1] = janet_wrap_number(scancode);
    switch (action) {
        case 0:
            args[2] = janet_ckeywordv("release");
            break;
        case 1:
            args[2] = janet_ckeywordv("press");
            break;
        case 2:
            args[2] = janet_ckeywordv("repeat");
            break;
        default:
            args[2] = janet_wrap_number(action);
            break;
    }

    JanetArray *mods_arr = janet_array(0);
    if (mods & GLFW_MOD_SHIFT) {
        janet_array_push(mods_arr, janet_ckeywordv("shift"));
    }
    if (mods & GLFW_MOD_CONTROL) {
        janet_array_push(mods_arr, janet_ckeywordv("control"));
    }
    if (mods & GLFW_MOD_ALT) {
        janet_array_push(mods_arr, janet_ckeywordv("alt"));
    }
    if (mods & GLFW_MOD_SUPER) {
        janet_array_push(mods_arr, janet_ckeywordv("super"));
    }
    if (mods & GLFW_MOD_CAPS_LOCK) {
        janet_array_push(mods_arr, janet_ckeywordv("caps-lock"));
    }
    if (mods & GLFW_MOD_NUM_LOCK) {
        janet_array_push(mods_arr, janet_ckeywordv("num-lock"));
    }
    args[3] = janet_wrap_array(mods_arr);
    
    janet_call(key_callback, 4, args);
}

static Janet cfun_SetKeyCallback(int32_t argc, Janet *argv)
{
    janet_fixarity(argc, 1);

    JanetFunction *f;
    if (janet_checktype(argv[0], JANET_NIL)) {
        f = NULL;
    } else {
        f = janet_getfunction(argv, 0);
    }

    if (NULL != key_callback) {
        janet_gcunroot(janet_wrap_function(key_callback));
    }

    key_callback = f;

    if (f) {
        janet_gcroot(janet_wrap_function(key_callback));
        glfwSetKeyCallback(GetGLFWWindow(), KeyCallback);
    } else {
        glfwSetKeyCallback(GetGLFWWindow(), NULL);
    }

    return janet_wrap_nil();
}

static JanetReg glfw_cfuns[] = {
    {"set-key-callback", cfun_SetKeyCallback, NULL},
    {NULL, NULL, NULL}};