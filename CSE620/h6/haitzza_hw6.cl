__kernel void conv(__read_only image2d_t srcImage,
                   __write_only image2d_t outImage,
                   int width, int height, sampler_t sampler,
                   __global float* conData,
                   int conWidth, int conHeight) {
    const int2 coords = {get_global_id(0), get_global_id(1)};
    int conIdx = 0;
    float tempR = 0.0f, tempG = 0.0f, tempB = 0.0f;
    for (int i = coords.y - conHeight / 2; i <= coords.y + conHeight / 2; i++) {
        if (i < 0 || i > height) {
            continue;
        }
        for (int j = coords.x - conWidth / 2;
                 j <= coords.x +  conWidth / 2; j++) {
            if (j < 0 || j > width) {
                continue;
            }
            int2 currCords = {j, i};
            uint4 pixel = read_imageui(srcImage, sampler, currCords);
            float currVal = conData[conIdx];
            tempR += currVal * pixel.x;
            tempG += currVal * pixel.y;
            tempB += currVal * pixel.z;
            conIdx++;            
        }
    }
    uint4 outPixel = {tempR, tempG, tempB, 255};
    write_imageui(outImage, coords, outPixel);
}
