/*
 *  Generating texture process: 
 *  1. glGenTexture(uint)
 *  2. bind texture
 *  3. extract texture with stb_img
 *  4. bind the img to our texture object
 *  5. set filter params
 *  
 *  Binding Texture to Vertex
 *  1. Update raw vertice data with x,y coords for texture placement (since we're using a 2d texture)
 *  2. Update the stride/offset/location for each attribute of the vertex
 *  3. Remember to call location for each bind action
 *
 *  notes: 
 *  it's going to be messy with my current vbo setup. this will most definitely 
 *  require a refactor later but I'm willing to push it till the tutorial tells
 *  me to do different
 *
 *
 * */
