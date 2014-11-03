__kernel void img_rotate(__read_only image2d_t srcImage,
                         __write_only image2d_t outImage,
                         int width, int height, sampler_t sampler,
                         float sinTheta, float cosTheta) {
    const int2 coords = {get_global_id(0), get_global_id(1)};
    const int2 p      = {width / 2, height / 2};
    const int2 flipCoords = {
        (cosTheta * (coords.x - p.x) + sinTheta * (coords.y - p.y)) + p.x,
        (cosTheta * (coords.y - p.y) - sinTheta * (coords.x - p.x)) + p.y
    };
    if ((flipCoords.x >= 0 && flipCoords.x < width) &&
        (flipCoords.y >= 0 && flipCoords.y < height)) {
        uint4 pixel = read_imageui(srcImage, sampler, coords);
        write_imageui(outImage, flipCoords, pixel);
    }
}
