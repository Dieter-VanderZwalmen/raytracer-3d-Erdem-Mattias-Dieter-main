URL=`git remote -v | grep origin | grep push | awk '{print($2)}'`
ORG=`echo $URL | cut -d/ -f4`
REPONAME=`echo $URL | cut -d/ -f5`
REPO="https://github.com/$ORG/$REPONAME"

gh issue create --title "Bouncy and Elastic Animation" --label enhancement --body http://3dcg.leone.ucll.be/extensions/animations/bounce-elastic/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Circular Animation" --label enhancement --body http://3dcg.leone.ucll.be/extensions/animations/circular/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Easing Library" --label enhancement --body http://3dcg.leone.ucll.be/extensions/animations/easing-library/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Lissajous Animation" --label enhancement --body http://3dcg.leone.ucll.be/extensions/animations/lissajous/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Animation Operations" --label enhancement --body http://3dcg.leone.ucll.be/extensions/animations/operations/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Polynomial Easing Functions" --label enhancement --body http://3dcg.leone.ucll.be/extensions/animations/polynomial-easing/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Depth of Field Camera" --label enhancement --body http://3dcg.leone.ucll.be/extensions/cameras/depth-of-field/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Fisheye Camera" --label enhancement --body http://3dcg.leone.ucll.be/extensions/cameras/fisheye/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Orthographic Camera" --label enhancement --body http://3dcg.leone.ucll.be/extensions/cameras/orthographic/explanations.html --project raytracer-test -R $REPO
gh issue create --title "MaterialProperties Default Values Redundancy" --label enhancement --body http://3dcg.leone.ucll.be/extensions/improvements/material-properties-defaults/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Translucency Optimization" --label enhancement --body http://3dcg.leone.ucll.be/extensions/improvements/translucency/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Scripting" --label enhancement --body http://3dcg.leone.ucll.be/extensions/introduction/scripting/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Area Lights" --label enhancement --body http://3dcg.leone.ucll.be/extensions/lights/area-light/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Directional Light" --label enhancement --body http://3dcg.leone.ucll.be/extensions/lights/directional-light/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Spot Lights" --label enhancement --body http://3dcg.leone.ucll.be/extensions/lights/spot-lights/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Marble" --label enhancement --body http://3dcg.leone.ucll.be/extensions/materials/marble/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Pattern Materials" --label enhancement --body http://3dcg.leone.ucll.be/extensions/materials/pattern/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Textures" --label enhancement --body http://3dcg.leone.ucll.be/extensions/materials/texture/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Material Transformation" --label enhancement --body http://3dcg.leone.ucll.be/extensions/materials/transformations/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Worley 2D" --label enhancement --body http://3dcg.leone.ucll.be/extensions/materials/worley/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Perlin" --label enhancement --body http://3dcg.leone.ucll.be/extensions/math/perlin/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Quaternions" --label enhancement --body http://3dcg.leone.ucll.be/extensions/math/quaternions/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Transformations" --label enhancement --body http://3dcg.leone.ucll.be/extensions/math/transformations/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Voronoi" --label enhancement --body http://3dcg.leone.ucll.be/extensions/math/voronoi/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Basics" --label enhancement --body http://3dcg.leone.ucll.be/extensions/patterns/basics/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Dalmatian Pattern" --label enhancement --body http://3dcg.leone.ucll.be/extensions/patterns/dalmatian/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Flower Pattern" --label enhancement --body http://3dcg.leone.ucll.be/extensions/patterns/flower/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Lambda Pattern" --label enhancement --body http://3dcg.leone.ucll.be/extensions/patterns/lambda/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Logic Operations" --label enhancement --body http://3dcg.leone.ucll.be/extensions/patterns/logic-operations/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Spiral Pattern" --label enhancement --body http://3dcg.leone.ucll.be/extensions/patterns/spiral/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Tiling" --label enhancement --body http://3dcg.leone.ucll.be/extensions/patterns/tiling/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Pattern Transformations" --label enhancement --body http://3dcg.leone.ucll.be/extensions/patterns/transformations/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Balanced Parallel Task Scheduler" --label enhancement --body http://3dcg.leone.ucll.be/extensions/performance/balanced-parallel-task-scheduler/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Naive Parallel Task Scheduler" --label enhancement --body http://3dcg.leone.ucll.be/extensions/performance/naive-parallel-task-scheduler/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Unbalanced Parallel Task Scheduler" --label enhancement --body http://3dcg.leone.ucll.be/extensions/performance/unbalanced-parallel-task-scheduler/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Motion Blur" --label enhancement --body http://3dcg.leone.ucll.be/extensions/pipeline/motion-blur/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Studio Pipeline Segment" --label enhancement --body http://3dcg.leone.ucll.be/extensions/pipeline/studio/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Binary Mesh" --label enhancement --body http://3dcg.leone.ucll.be/extensions/primitives/binary-mesh/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Bounding Box Accelerator" --label enhancement --body http://3dcg.leone.ucll.be/extensions/primitives/bounding-box-accelerator/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Box" --label enhancement --body http://3dcg.leone.ucll.be/extensions/primitives/box/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Bumpifier" --label enhancement --body http://3dcg.leone.ucll.be/extensions/primitives/bumpifier/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Coarse" --label enhancement --body http://3dcg.leone.ucll.be/extensions/primitives/coarse/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Cone" --label enhancement --body http://3dcg.leone.ucll.be/extensions/primitives/cone/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Cropper" --label enhancement --body http://3dcg.leone.ucll.be/extensions/primitives/cropper/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Constructive Solid Geometry" --label enhancement --body http://3dcg.leone.ucll.be/extensions/primitives/csg/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Cylinder" --label enhancement --body http://3dcg.leone.ucll.be/extensions/primitives/cylinder/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Disk" --label enhancement --body http://3dcg.leone.ucll.be/extensions/primitives/disk/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Mesh" --label enhancement --body http://3dcg.leone.ucll.be/extensions/primitives/mesh/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Planes" --label enhancement --body http://3dcg.leone.ucll.be/extensions/primitives/plane/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Resizer" --label enhancement --body http://3dcg.leone.ucll.be/extensions/primitives/resizer/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Smooth Mesh" --label enhancement --body http://3dcg.leone.ucll.be/extensions/primitives/smooth-mesh/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Textured Mesh" --label enhancement --body http://3dcg.leone.ucll.be/extensions/primitives/textured-mesh/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Transformations" --label enhancement --body http://3dcg.leone.ucll.be/extensions/primitives/transformations/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Triangle" --label enhancement --body http://3dcg.leone.ucll.be/extensions/primitives/triangle/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Ray Tracer v1" --label enhancement --body http://3dcg.leone.ucll.be/extensions/ray-tracers/v1/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Ray Tracer v2" --label enhancement --body http://3dcg.leone.ucll.be/extensions/ray-tracers/v2/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Ray Tracer v3" --label enhancement --body http://3dcg.leone.ucll.be/extensions/ray-tracers/v3/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Ray Tracer v4" --label enhancement --body http://3dcg.leone.ucll.be/extensions/ray-tracers/v4/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Ray Tracer v5" --label enhancement --body http://3dcg.leone.ucll.be/extensions/ray-tracers/v5/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Ray Tracer v6" --label enhancement --body http://3dcg.leone.ucll.be/extensions/ray-tracers/v6/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Ray Tracer v7" --label enhancement --body http://3dcg.leone.ucll.be/extensions/ray-tracers/v7/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Ray Tracer v8" --label enhancement --body http://3dcg.leone.ucll.be/extensions/ray-tracers/v8/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Cartoon Renderer" --label enhancement --body http://3dcg.leone.ucll.be/extensions/renderers/cartoon/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Edge Renderer" --label enhancement --body http://3dcg.leone.ucll.be/extensions/renderers/edge/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Masking Renderer" --label enhancement --body http://3dcg.leone.ucll.be/extensions/renderers/masking/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Multijittered Sampler" --label enhancement --body http://3dcg.leone.ucll.be/extensions/samplers/multijittered/explanations.html --project raytracer-test -R $REPO
gh issue create --title "N-Rooks Sampler" --label enhancement --body http://3dcg.leone.ucll.be/extensions/samplers/nrooks/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Random Sampler" --label enhancement --body http://3dcg.leone.ucll.be/extensions/samplers/random/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Stratified Sampler" --label enhancement --body http://3dcg.leone.ucll.be/extensions/samplers/stratified/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Stratified - Half Jittered Sampler" --label enhancement --body http://3dcg.leone.ucll.be/extensions/samplers/stratified-half-jittered/explanations.html --project raytracer-test -R $REPO
gh issue create --title "Stratified - Jittered Sampler" --label enhancement --body http://3dcg.leone.ucll.be/extensions/samplers/stratified-jittered/explanations.html --project raytracer-test -R $REPO
