local qmk_root = os.getenv("QMK_HOME")
local clangd_bin = os.getenv("NIX_CLANGD_PATH")

if not (qmk_root and clangd_bin) then return end

return {
    cmd = {
        clangd_bin,
        '--clang-tidy',
        '--background-index',
        '--header-insertion=never',
        '--compile-commands-dir=' .. qmk_root,
    },
    filetypes = { 'c', 'h', 'cpp', 'hpp' },
    root_dir = qmk_root,
    capabilities = { offsetEncoding = { "utf-16" } },
}
