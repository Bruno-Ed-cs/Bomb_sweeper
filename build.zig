const std = @import("std");

const flags = [_][] const u8 {
    "-lm",

};

const source_files = [_][]const u8 { 

    "bombs.c",
    "cJSON.c",
    "explosions.c",
    "game.c",
    "globals.c",
    "main.c",
    "menus.c",
    "player.c",
    "score.c",
    "system.c",
    "tilemap.c",

};

pub fn build(b: *std.Build) void {

    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    var exe = b.addExecutable(.{
        .name = "bombsweeper",
        .root_module = b.addModule("main", .{
            .optimize = optimize,
            .target = target,
            .link_libc = true,

        }),
    });


    const lib_path = switch(target.result.os.tag) {

        .windows => b.path("lib/Windows/"),
        .linux => b.path("lib/Linux/x11/lib/"),

        else => @panic("Target not supported")

    };
    
    exe.addLibraryPath(lib_path);

    exe.linkSystemLibrary("raylib");

    //exe.addIncludePath(b.path("include"));

    exe.addCSourceFiles(.{
        .files = source_files[0..],
    });


    b.installArtifact(exe);

    const lib_folders = b.addInstallDirectory(.{
        .source_dir = lib_path,
        .install_dir = .bin,
        .install_subdir = "lib"
    });

    const asset_folder = b.addInstallDirectory(.{
        .source_dir = b.path("assets"),
        .install_dir = .bin,
        .install_subdir = "assets"

    });

    const build_step = b.getInstallStep();
    build_step.dependOn(&lib_folders.step);
    build_step.dependOn(&asset_folder.step);

    const run = b.addRunArtifact(exe);
    const step = b.step("run", "run game");
    step.dependOn(&run.step);

}
