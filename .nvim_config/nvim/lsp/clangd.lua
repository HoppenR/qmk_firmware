local qmk_root = os.getenv("QMK_HOME")

if not qmk_root then return end

return {
    cmd = {
        'clangd',
        '--clang-tidy',
        '--background-index',
        '--header-insertion=never',
        '--compile-commands-dir=' .. qmk_root,
    },
    filetypes = { 'c', 'h', 'cpp', 'hpp' },
    root_dir = qmk_root,
    capabilities = { offsetEncoding = { "utf-16" } },
}
