## image_transport_node
`image_transport_node` is a demo node that publishes images over `image_transport`.

## How to compress nodes
1. install `<ros distro>-compressed-image-transport`
2. `ros2 run image_transport republish raw in:=/camera/image compressed out:=/camera/compressed`
3. `ros2 node info /republisher` will report that compressed images are published on `/camera/compressed`

