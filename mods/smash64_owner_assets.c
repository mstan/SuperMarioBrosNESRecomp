#include "smash64_owner_assets.h"

#include <SDL.h>

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALCON_CACHE_PREFIX "falcon-final-r1-e2929e10fccc0aa84e5776227e798abc07cedabf-"
#define PIKACHU_CACHE_PREFIX "pikachu-final-r9-"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define FALCON_HELPER_NAME "falcon_owner_assets.exe"

static int utf8_to_wide(const char *source, wchar_t *target, size_t capacity)
{
    int count;
    if (!source || !target || capacity == 0 || capacity > INT_MAX) return 0;
    count = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, source, -1,
                                target, (int)capacity);
    return count > 0;
}

static int append_quoted(wchar_t *command, size_t capacity, size_t *length,
                         const wchar_t *argument)
{
    size_t backslashes = 0;
    const wchar_t *cursor;
#define APPEND_WIDE(ch) do { \
    if (*length + 1 >= capacity) return 0; \
    command[(*length)++] = (ch); \
} while (0)
    if (*length) APPEND_WIDE(L' ');
    APPEND_WIDE(L'"');
    for (cursor = argument; *cursor; ++cursor) {
        if (*cursor == L'\\') {
            backslashes++;
            continue;
        }
        if (*cursor == L'"') {
            while (backslashes > 0) { APPEND_WIDE(L'\\'); backslashes--; }
            APPEND_WIDE(L'\\');
        } else {
            while (backslashes > 0) { APPEND_WIDE(L'\\'); backslashes--; }
        }
        backslashes = 0;
        APPEND_WIDE(*cursor);
    }
    while (backslashes > 0) {
        APPEND_WIDE(L'\\');
        APPEND_WIDE(L'\\');
        backslashes--;
    }
    APPEND_WIDE(L'"');
    command[*length] = L'\0';
#undef APPEND_WIDE
    return 1;
}

static int run_helper(const char *helper, const char *rom,
                      const char *cache, const char *result,
                      const char *fighter, const char *costume)
{
    wchar_t helper_w[2048], rom_w[2048], cache_w[2048], result_w[2048];
    wchar_t fighter_w[64], costume_w[16];
    wchar_t flag_rom[] = L"--rom";
    wchar_t flag_cache[] = L"--cache-root";
    wchar_t flag_result[] = L"--result-file";
    wchar_t flag_fighter[] = L"--fighter";
    wchar_t flag_costume[] = L"--costume";
    wchar_t command[8192];
    size_t length = 0;
    STARTUPINFOW startup;
    PROCESS_INFORMATION process;
    DWORD wait_result, exit_code = 1;
    SECURITY_ATTRIBUTES security;
    HANDLE null_output = INVALID_HANDLE_VALUE;

    if (!utf8_to_wide(helper, helper_w, sizeof(helper_w) / sizeof(helper_w[0])) ||
        !utf8_to_wide(rom, rom_w, sizeof(rom_w) / sizeof(rom_w[0])) ||
        !utf8_to_wide(cache, cache_w, sizeof(cache_w) / sizeof(cache_w[0])) ||
        !utf8_to_wide(result, result_w, sizeof(result_w) / sizeof(result_w[0])) ||
        !utf8_to_wide(fighter, fighter_w,
                      sizeof(fighter_w) / sizeof(fighter_w[0])) ||
        !utf8_to_wide(costume, costume_w,
                      sizeof(costume_w) / sizeof(costume_w[0])))
        return 0;
    command[0] = L'\0';
    if (!append_quoted(command, sizeof(command) / sizeof(command[0]), &length, helper_w) ||
        !append_quoted(command, sizeof(command) / sizeof(command[0]), &length, flag_rom) ||
        !append_quoted(command, sizeof(command) / sizeof(command[0]), &length, rom_w) ||
        !append_quoted(command, sizeof(command) / sizeof(command[0]), &length, flag_cache) ||
        !append_quoted(command, sizeof(command) / sizeof(command[0]), &length, cache_w) ||
        !append_quoted(command, sizeof(command) / sizeof(command[0]), &length, flag_result) ||
        !append_quoted(command, sizeof(command) / sizeof(command[0]), &length, result_w) ||
        !append_quoted(command, sizeof(command) / sizeof(command[0]), &length, flag_fighter) ||
        !append_quoted(command, sizeof(command) / sizeof(command[0]), &length, fighter_w) ||
        !append_quoted(command, sizeof(command) / sizeof(command[0]), &length, flag_costume) ||
        !append_quoted(command, sizeof(command) / sizeof(command[0]), &length, costume_w))
        return 0;

    memset(&startup, 0, sizeof(startup));
    memset(&process, 0, sizeof(process));
    memset(&security, 0, sizeof(security));
    security.nLength = sizeof(security);
    security.bInheritHandle = TRUE;
    null_output = CreateFileW(L"NUL", GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE,
                              &security, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (null_output == INVALID_HANDLE_VALUE) return 0;
    startup.cb = sizeof(startup);
    startup.dwFlags = STARTF_USESTDHANDLES;
    startup.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    startup.hStdOutput = null_output;
    startup.hStdError = null_output;
    if (!CreateProcessW(helper_w, command, NULL, NULL, TRUE, CREATE_NO_WINDOW,
                        NULL, NULL, &startup, &process)) {
        CloseHandle(null_output);
        return 0;
    }
    CloseHandle(null_output);
    wait_result = WaitForSingleObject(process.hProcess, 180000u);
    if (wait_result == WAIT_TIMEOUT) {
        TerminateProcess(process.hProcess, 1u);
        WaitForSingleObject(process.hProcess, 5000u);
    } else if (wait_result == WAIT_OBJECT_0) {
        GetExitCodeProcess(process.hProcess, &exit_code);
    }
    CloseHandle(process.hThread);
    CloseHandle(process.hProcess);
    return wait_result == WAIT_OBJECT_0 && exit_code == 0;
}

static int read_cache_name(const char *path, const char *prefix,
                           char *name, size_t capacity)
{
    wchar_t path_w[2048];
    FILE *file;
    size_t length, i;
    if (!utf8_to_wide(path, path_w, sizeof(path_w) / sizeof(path_w[0]))) return 0;
    file = _wfopen(path_w, L"rb");
    if (!file) return 0;
    length = fread(name, 1, capacity - 1, file);
    if (ferror(file) || !feof(file)) {
        fclose(file);
        return 0;
    }
    fclose(file);
    while (length && (name[length - 1] == '\r' || name[length - 1] == '\n')) length--;
    name[length] = '\0';
    if (strncmp(name, prefix, strlen(prefix)) != 0)
        return 0;
    for (i = 0; i < length; ++i) {
        unsigned char ch = (unsigned char)name[i];
        if (!(isalnum(ch) || ch == '-')) return 0;
    }
    return length > strlen(prefix);
}

int smash64_owner_assets_prepare_character(const char *owner_rom_path,
                                           const char *fighter_key,
                                           int costume,
                                           char *cache_root,
                                           size_t cache_root_size)
{
    char *base = NULL, *pref = NULL;
    char helper[2048], parent[2048], result[2048], name[512];
    char prefix[128], costume_text[16];
    int helper_len, parent_len, result_len, root_len;
    int ok = 0;
    unsigned long process_id = GetCurrentProcessId();
    if (!owner_rom_path || !*owner_rom_path || !fighter_key ||
        !cache_root || cache_root_size == 0 || costume < 0 || costume > 3)
        return 0;
    if (strcmp(fighter_key, "captain-falcon") == 0) {
        if (costume != 0) return 0;
        snprintf(prefix, sizeof(prefix), "%s", FALCON_CACHE_PREFIX);
    } else if (strcmp(fighter_key, "pikachu") == 0) {
        snprintf(prefix, sizeof(prefix), "%sc%d-", PIKACHU_CACHE_PREFIX,
                 costume);
    } else return 0;
    snprintf(costume_text, sizeof(costume_text), "%d", costume);
    result[0] = '\0';
    base = SDL_GetBasePath();
    pref = SDL_GetPrefPath("NESRecomp", "SuperMarioBrosRecomp");
    if (!base || !pref) goto done;
    helper_len = snprintf(helper, sizeof(helper), "%s%s", base, FALCON_HELPER_NAME);
    parent_len = snprintf(parent, sizeof(parent), "%ssmash64", pref);
    if (helper_len < 0 || (size_t)helper_len >= sizeof(helper) ||
        parent_len < 0 || (size_t)parent_len >= sizeof(parent))
        goto done;
    result_len = snprintf(result, sizeof(result), "%s/active-cache-%lu.txt",
                          parent, process_id);
    if (result_len < 0 || (size_t)result_len >= sizeof(result))
        goto done;
    (void)remove(result);
    if (!run_helper(helper, owner_rom_path, parent, result, fighter_key,
                    costume_text) ||
        !read_cache_name(result, prefix, name, sizeof(name)))
        goto done;
    root_len = snprintf(cache_root, cache_root_size, "%s/%s", parent, name);
    if (root_len < 0 || (size_t)root_len >= cache_root_size)
        goto done;
    ok = 1;
done:
    if (result[0]) (void)remove(result);
    if (base) SDL_free(base);
    if (pref) SDL_free(pref);
    if (!ok && cache_root_size) cache_root[0] = '\0';
    return ok;
}

int smash64_owner_assets_prepare(const char *owner_rom_path,
                                 char *cache_root, size_t cache_root_size)
{
    return smash64_owner_assets_prepare_character(
        owner_rom_path, "captain-falcon", 0, cache_root, cache_root_size);
}

#else

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define FALCON_HELPER_NAME "falcon_owner_assets"

static int run_helper(const char *helper, const char *rom,
                      const char *cache, const char *result,
                      const char *fighter, const char *costume)
{
    pid_t child;
    int status = 0;
    unsigned elapsed_ms = 0;
    char *const arguments[] = {
        (char *)helper,
        (char *)"--rom", (char *)rom,
        (char *)"--cache-root", (char *)cache,
        (char *)"--result-file", (char *)result,
        (char *)"--fighter", (char *)fighter,
        (char *)"--costume", (char *)costume,
        NULL
    };

    child = fork();
    if (child < 0) return 0;
    if (child == 0) {
        int null_output;
        (void)setpgid(0, 0);
        if (!getenv("NESRECOMP_FALCON_OWNER_DEBUG")) {
            null_output = open("/dev/null", O_WRONLY);
            if (null_output >= 0) {
                (void)dup2(null_output, STDOUT_FILENO);
                (void)dup2(null_output, STDERR_FILENO);
                if (null_output > STDERR_FILENO) close(null_output);
            }
        }
        execv(helper, arguments);
        _exit(127);
    }

    (void)setpgid(child, child);
    while (elapsed_ms < 180000u) {
        pid_t result_pid = waitpid(child, &status, WNOHANG);
        if (result_pid == child)
            return WIFEXITED(status) && WEXITSTATUS(status) == 0;
        if (result_pid < 0 && errno != EINTR) return 0;
        SDL_Delay(50u);
        elapsed_ms += 50u;
    }
    (void)kill(-child, SIGKILL);
    while (waitpid(child, &status, 0) < 0 && errno == EINTR) {}
    return 0;
}

static int read_cache_name(const char *path, const char *prefix,
                           char *name, size_t capacity)
{
    FILE *file;
    size_t length, i;
    if (!path || !name || capacity < 2) return 0;
    file = fopen(path, "rb");
    if (!file) return 0;
    length = fread(name, 1, capacity - 1, file);
    if (ferror(file) || !feof(file)) {
        fclose(file);
        return 0;
    }
    fclose(file);
    while (length && (name[length - 1] == '\r' || name[length - 1] == '\n')) length--;
    name[length] = '\0';
    if (strncmp(name, prefix, strlen(prefix)) != 0)
        return 0;
    for (i = 0; i < length; ++i) {
        unsigned char ch = (unsigned char)name[i];
        if (!(isalnum(ch) || ch == '-')) return 0;
    }
    return length > strlen(prefix);
}

int smash64_owner_assets_prepare_character(const char *owner_rom_path,
                                           const char *fighter_key,
                                           int costume,
                                           char *cache_root,
                                           size_t cache_root_size)
{
    char *base = NULL, *pref = NULL;
    char helper[2048], parent[2048], result[2048], name[512];
    char prefix[128], costume_text[16];
    int helper_len, parent_len, result_len, root_len;
    int ok = 0;
    long process_id;
    if (!owner_rom_path || !*owner_rom_path || !fighter_key ||
        !cache_root || cache_root_size == 0 || costume < 0 || costume > 3)
        return 0;
    if (strcmp(fighter_key, "captain-falcon") == 0) {
        if (costume != 0) return 0;
        snprintf(prefix, sizeof(prefix), "%s", FALCON_CACHE_PREFIX);
    } else if (strcmp(fighter_key, "pikachu") == 0) {
        snprintf(prefix, sizeof(prefix), "%sc%d-", PIKACHU_CACHE_PREFIX,
                 costume);
    } else return 0;
    snprintf(costume_text, sizeof(costume_text), "%d", costume);
    result[0] = '\0';
    base = SDL_GetBasePath();
    pref = SDL_GetPrefPath("NESRecomp", "SuperMarioBrosRecomp");
    if (!base || !pref) goto done;
    process_id = (long)getpid();
    helper_len = snprintf(helper, sizeof(helper), "%s%s", base, FALCON_HELPER_NAME);
    parent_len = snprintf(parent, sizeof(parent), "%ssmash64", pref);
    if (helper_len < 0 || (size_t)helper_len >= sizeof(helper) ||
        parent_len < 0 || (size_t)parent_len >= sizeof(parent))
        goto done;
    result_len = snprintf(result, sizeof(result), "%s/active-cache-%ld.txt",
                          parent, process_id);
    if (result_len < 0 || (size_t)result_len >= sizeof(result)) goto done;
    (void)unlink(result);
    if (!run_helper(helper, owner_rom_path, parent, result, fighter_key,
                    costume_text) ||
        !read_cache_name(result, prefix, name, sizeof(name)))
        goto done;
    root_len = snprintf(cache_root, cache_root_size, "%s/%s", parent, name);
    if (root_len < 0 || (size_t)root_len >= cache_root_size) goto done;
    ok = 1;
done:
    if (result[0]) (void)unlink(result);
    if (base) SDL_free(base);
    if (pref) SDL_free(pref);
    if (!ok && cache_root_size) cache_root[0] = '\0';
    return ok;
}

int smash64_owner_assets_prepare(const char *owner_rom_path,
                                 char *cache_root, size_t cache_root_size)
{
    return smash64_owner_assets_prepare_character(
        owner_rom_path, "captain-falcon", 0, cache_root, cache_root_size);
}

#endif
