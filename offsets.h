#pragma once

#include <cstdint>
#include <string>

namespace Offsets {

    namespace AirProperties {
        inline  uintptr_t AirDensity ;
        inline  uintptr_t GlobalWind ;
    }

    namespace AnimationTrack {
        inline  uintptr_t Animation ;
        inline  uintptr_t Animator ;
        inline  uintptr_t IsPlaying ;
        inline  uintptr_t Looped ;
        inline  uintptr_t Speed ;
        inline  uintptr_t TimePosition ;
    }

    namespace Animator {
        inline  uintptr_t ActiveAnimations ;
    }

    namespace Atmosphere {
        inline  uintptr_t Color ;
        inline  uintptr_t Decay ;
        inline  uintptr_t Density ;
        inline  uintptr_t Glare ;
        inline  uintptr_t Haze ;
        inline  uintptr_t Offset ;
    }

    namespace Attachment {
        inline  uintptr_t Position ;
    }

    namespace Attribute {
        inline  uintptr_t Key ;
        inline  uintptr_t Size ;
        inline  uintptr_t Value ;
    }

    namespace AttributesMap {
        inline  uintptr_t Attributes ;
        inline  uintptr_t Length ;
    }

    namespace BasePart {
        inline  uintptr_t CastShadow ;
        inline  uintptr_t Color3 ;
        inline  uintptr_t Locked ;
        inline  uintptr_t Massless ;
        inline  uintptr_t Primitive ;
        inline  uintptr_t Reflectance ;
        inline  uintptr_t Shape ;
        inline  uintptr_t Transparency ;
    }

    namespace Beam {
        inline  uintptr_t Attachment0 ;
        inline  uintptr_t Attachment1 ;
        inline  uintptr_t Brightness ;
        inline  uintptr_t CurveSize0 ;
        inline  uintptr_t CurveSize1 ;
        inline  uintptr_t LightEmission ;
        inline  uintptr_t LightInfluence ;
        inline  uintptr_t Texture ;
        inline  uintptr_t TextureLength ;
        inline  uintptr_t TextureSpeed ;
        inline  uintptr_t Width0 ;
        inline  uintptr_t Width1 ;
        inline  uintptr_t ZOffset ;
    }

    namespace BloomEffect {
        inline  uintptr_t Enabled ;
        inline  uintptr_t Intensity ;
        inline  uintptr_t Size ;
        inline  uintptr_t Threshold ;
    }

    namespace BlurEffect {
        inline  uintptr_t Enabled ;
        inline  uintptr_t Size ;
    }

    namespace ByteCode {
        inline  uintptr_t Pointer ;
        inline  uintptr_t Size ;
    }

    namespace Camera {
        inline  uintptr_t CameraSubject ;
        inline  uintptr_t CameraType ;
        inline  uintptr_t FieldOfView ;
        inline  uintptr_t ImagePlaneDepth ;
        inline  uintptr_t Position ;
        inline  uintptr_t Rotation ;
        inline  uintptr_t Viewport ;
        inline  uintptr_t ViewportSize ;
    }

    namespace CharacterMesh {
        inline  uintptr_t BaseTextureId ;
        inline  uintptr_t BodyPart ;
        inline  uintptr_t MeshId ;
        inline  uintptr_t OverlayTextureId ;
    }

    namespace ClickDetector {
        inline  uintptr_t MaxActivationDistance ;
        inline  uintptr_t MouseIcon ;
    }

    namespace Clothing {
        inline  uintptr_t Color3 ;
        inline  uintptr_t Template ;
    }

    namespace ColorCorrectionEffect {
        inline  uintptr_t Brightness ;
        inline  uintptr_t Contrast ;
        inline  uintptr_t Enabled ;
        inline  uintptr_t TintColor ;
    }

    namespace ColorGradingEffect {
        inline  uintptr_t Enabled ;
        inline  uintptr_t TonemapperPreset ;
    }

    namespace DataModel {
        inline  uintptr_t CreatorId ;
        inline  uintptr_t GameId ;
        inline  uintptr_t GameLoaded ;
        inline  uintptr_t JobId ;
        inline  uintptr_t PlaceId ;
        inline  uintptr_t PlaceVersion ;
        inline  uintptr_t PrimitiveCount ;
        inline  uintptr_t ScriptContext ;
        inline  uintptr_t ServerIP ;
        inline  uintptr_t ToRenderView1 ;
        inline  uintptr_t ToRenderView2 ;
        inline  uintptr_t ToRenderView3 ;
        inline  uintptr_t Workspace ;
    }

    namespace DepthOfFieldEffect {
        inline  uintptr_t Enabled ;
        inline  uintptr_t FarIntensity ;
        inline  uintptr_t FocusDistance ;
        inline  uintptr_t InFocusRadius ;
        inline  uintptr_t NearIntensity ;
    }

    namespace DragDetector {
        inline  uintptr_t ActivatedCursorIcon ;
        inline  uintptr_t CursorIcon ;
        inline  uintptr_t MaxActivationDistance ;
        inline  uintptr_t MaxDragAngle ;
        inline  uintptr_t MaxDragTranslation ;
        inline  uintptr_t MaxForce ;
        inline  uintptr_t MaxTorque ;
        inline  uintptr_t MinDragAngle ;
        inline  uintptr_t MinDragTranslation ;
        inline  uintptr_t ReferenceInstance ;
        inline  uintptr_t Responsiveness ;
    }

    namespace FakeDataModel {
        inline  uintptr_t Pointer ;
        inline  uintptr_t RealDataModel ;
    }

    namespace GuiBase2D {
        inline  uintptr_t AbsolutePosition ;
        inline  uintptr_t AbsoluteRotation ;
        inline  uintptr_t AbsoluteSize ;
    }

    namespace GuiObject {
        inline  uintptr_t BackgroundColor3 ;
        inline  uintptr_t BackgroundTransparency ;
        inline  uintptr_t BorderColor3 ;
        inline  uintptr_t Image ;
        inline  uintptr_t LayoutOrder ;
        inline  uintptr_t Position ;
        inline  uintptr_t RichText ;
        inline  uintptr_t Rotation ;
        inline  uintptr_t ScreenGui_Enabled ;
        inline  uintptr_t Size ;
        inline  uintptr_t Text ;
        inline  uintptr_t TextColor3 ;
        inline  uintptr_t Visible ;
        inline  uintptr_t ZIndex ;
    }

    namespace Humanoid {
        inline  uintptr_t AutoJumpEnabled ;
        inline  uintptr_t AutoRotate ;
        inline  uintptr_t AutomaticScalingEnabled ;
        inline  uintptr_t BreakJointsOnDeath ;
        inline  uintptr_t CameraOffset ;
        inline  uintptr_t DisplayDistanceType ;
        inline  uintptr_t DisplayName ;
        inline  uintptr_t EvaluateStateMachine ;
        inline  uintptr_t FloorMaterial ;
        inline  uintptr_t Health ;
        inline  uintptr_t HealthDisplayDistance ;
        inline  uintptr_t HealthDisplayType ;
        inline  uintptr_t HipHeight ;
        inline  uintptr_t HumanoidRootPart ;
        inline  uintptr_t HumanoidState ;
        inline  uintptr_t HumanoidStateID ;
        inline  uintptr_t IsWalking ;
        inline  uintptr_t Jump ;
        inline  uintptr_t JumpHeight ;
        inline  uintptr_t JumpPower ;
        inline  uintptr_t MaxHealth ;
        inline  uintptr_t MaxSlopeAngle ;
        inline  uintptr_t MoveDirection ;
        inline  uintptr_t MoveToPart ;
        inline  uintptr_t MoveToPoint ;
        inline  uintptr_t NameDisplayDistance ;
        inline  uintptr_t NameOcclusion ;
        inline  uintptr_t PlatformStand ;
        inline  uintptr_t PlatformStatePointer ;
        inline  uintptr_t RequiresNeck ;
        inline  uintptr_t RigType ;
        inline  uintptr_t SeatPart ;
        inline  uintptr_t Sit ;
        inline  uintptr_t TargetPoint ;
        inline  uintptr_t UseJumpPower ;
        inline  uintptr_t WalkTimer ;
        inline  uintptr_t Walkspeed ;
        inline  uintptr_t WalkspeedCheck ;
    }

    namespace Instance {
        inline  uintptr_t ChildrenEnd ;
        inline  uintptr_t ChildrenStart ;
        inline  uintptr_t ClassBase ;
        inline  uintptr_t ClassDescriptor ;
        inline  uintptr_t ClassDescriptorToClassName ;
        inline  uintptr_t ClassName ;
        inline  uintptr_t ComponentMap ;
        inline  uintptr_t Name ;
        inline  uintptr_t NameContainer ;
        inline  uintptr_t Parent ;
        inline  uintptr_t This ;
    }

    namespace Lighting {
        inline  uintptr_t Ambient ;
        inline  uintptr_t Brightness ;
        inline  uintptr_t ClockTime ;
        inline  uintptr_t ColorShift_Bottom ;
        inline  uintptr_t ColorShift_Top ;
        inline  uintptr_t EnvironmentDiffuseScale ;
        inline  uintptr_t EnvironmentSpecularScale ;
        inline  uintptr_t ExposureCompensation ;
        inline  uintptr_t FogColor ;
        inline  uintptr_t FogEnd ;
        inline  uintptr_t FogStart ;
        inline  uintptr_t GeographicLatitude ;
        inline  uintptr_t GlobalShadows ;
        inline  uintptr_t GradientBottom ;
        inline  uintptr_t GradientTop ;
        inline  uintptr_t LightColor ;
        inline  uintptr_t LightDirection ;
        inline  uintptr_t MoonPosition ;
        inline  uintptr_t OutdoorAmbient ;
        inline  uintptr_t Sky ;
        inline  uintptr_t Source ;
        inline  uintptr_t SunPosition ;
    }

    namespace LocalScript {
        inline  uintptr_t ByteCode ;
        inline  uintptr_t GUID ;
        inline  uintptr_t Hash ;
    }

    namespace MaterialColors {
        inline  uintptr_t Asphalt ;
        inline  uintptr_t Basalt ;
        inline  uintptr_t Brick ;
        inline  uintptr_t Cobblestone ;
        inline  uintptr_t Concrete ;
        inline  uintptr_t CrackedLava ;
        inline  uintptr_t Glacier ;
        inline  uintptr_t Grass ;
        inline  uintptr_t Ground ;
        inline  uintptr_t Ice ;
        inline  uintptr_t LeafyGrass ;
        inline  uintptr_t Limestone ;
        inline  uintptr_t Mud ;
        inline  uintptr_t Pavement ;
        inline  uintptr_t Rock ;
        inline  uintptr_t Salt ;
        inline  uintptr_t Sand ;
        inline  uintptr_t Sandstone ;
        inline  uintptr_t Slate ;
        inline  uintptr_t Snow ;
        inline  uintptr_t WoodPlanks ;
    }

    namespace MeshContentProvider {
        inline  uintptr_t AssetID ;
        inline  uintptr_t Cache ;
        inline  uintptr_t LRUCache ;
        inline  uintptr_t MeshData ;
        inline  uintptr_t ToMeshData ;
    }

    namespace MeshData {
        inline  uintptr_t FaceEnd ;
        inline  uintptr_t FaceStart ;
        inline  uintptr_t VertexEnd ;
        inline  uintptr_t VertexStart ;
    }

    namespace MeshPart {
        inline  uintptr_t MeshId ;
        inline  uintptr_t Texture ;
    }

    namespace Misc {
        inline  uintptr_t Adornee ;
        inline  uintptr_t AnimationId ;
        inline  uintptr_t StringLength ;
        inline  uintptr_t Value ;
    }

    namespace Model {
        inline  uintptr_t PrimaryPart ;
        inline  uintptr_t Scale ;
    }

    namespace ModuleScript {
        inline  uintptr_t ByteCode ;
        inline  uintptr_t GUID ;
        inline  uintptr_t Hash ;
        inline  uintptr_t IsCoreScript ;
    }

    namespace MouseService {
        inline  uintptr_t InputObject ;
        inline  uintptr_t InputObject2 ;
        inline  uintptr_t MousePosition ;
        inline  uintptr_t SensitivityPointer ;
    }

    namespace ParticleEmitter {
        inline  uintptr_t Acceleration ;
        inline  uintptr_t Brightness ;
        inline  uintptr_t Drag ;
        inline  uintptr_t Lifetime ;
        inline  uintptr_t LightEmission ;
        inline  uintptr_t LightInfluence ;
        inline  uintptr_t Rate ;
        inline  uintptr_t RotSpeed ;
        inline  uintptr_t Rotation ;
        inline  uintptr_t Speed ;
        inline  uintptr_t SpreadAngle ;
        inline  uintptr_t Texture ;
        inline  uintptr_t TimeScale ;
        inline  uintptr_t VelocityInheritance ;
        inline  uintptr_t ZOffset ;
    }

    namespace Player {
        inline  uintptr_t AccountAge ;
        inline  uintptr_t CameraMode ;
        inline  uintptr_t DisplayName ;
        inline  uintptr_t HealthDisplayDistance ;
        inline  uintptr_t LocalPlayer ;
        inline  uintptr_t LocaleId ;
        inline  uintptr_t MaxZoomDistance ;
        inline  uintptr_t MinZoomDistance ;
        inline  uintptr_t ModelInstance ;
        inline  uintptr_t Mouse ;
        inline  uintptr_t NameDisplayDistance ;
        inline  uintptr_t Team ;
        inline  uintptr_t TeamColor ;
        inline  uintptr_t UserId ;
    }

    namespace PlayerConfigurer {
        inline  uintptr_t Pointer ;
    }

    namespace PlayerMouse {
        inline  uintptr_t Icon ;
        inline  uintptr_t Workspace ;
    }

    namespace Primitive {
        inline  uintptr_t AssemblyAngularVelocity ;
        inline  uintptr_t AssemblyLinearVelocity ;
        inline  uintptr_t Flags ;
        inline  uintptr_t Material ;
        inline  uintptr_t Owner ;
        inline  uintptr_t Position ;
        inline  uintptr_t Rotation ;
        inline  uintptr_t Size ;
        inline  uintptr_t Validate ;
    }

    namespace PrimitiveFlags {
        inline  uintptr_t Anchored ;
        inline  uintptr_t CanCollide ;
        inline  uintptr_t CanQuery ;
        inline  uintptr_t CanTouch ;
    }

    namespace ProximityPrompt {
        inline  uintptr_t ActionText ;
        inline  uintptr_t Enabled ;
        inline  uintptr_t GamepadKeyCode ;
        inline  uintptr_t HoldDuration ;
        inline  uintptr_t KeyCode ;
        inline  uintptr_t MaxActivationDistance ;
        inline  uintptr_t ObjectText ;
        inline  uintptr_t RequiresLineOfSight ;
    }

    namespace RenderJob {
        inline  uintptr_t FakeDataModel ;
        inline  uintptr_t RealDataModel ;
        inline  uintptr_t RenderView ;
    }

    namespace RenderView {
        inline  uintptr_t DeviceD3D11 ;
        inline  uintptr_t LightingValid ;
        inline  uintptr_t SkyValid ;
        inline  uintptr_t VisualEngine ;
    }

    namespace RunService {
        inline  uintptr_t HeartbeatFPS ;
        inline  uintptr_t HeartbeatTask ;
    }

    namespace Script {
        inline  uintptr_t ByteCode ;
        inline  uintptr_t GUID ;
        inline  uintptr_t Hash ;
    }

    namespace ScriptContext {
        inline  uintptr_t RequireBypass ;
    }

    namespace Seat {
        inline  uintptr_t Occupant ;
    }

    namespace Sky {
        inline  uintptr_t MoonAngularSize ;
        inline  uintptr_t MoonTextureId ;
        inline  uintptr_t SkyboxBk ;
        inline  uintptr_t SkyboxDn ;
        inline  uintptr_t SkyboxFt ;
        inline  uintptr_t SkyboxLf ;
        inline  uintptr_t SkyboxOrientation ;
        inline  uintptr_t SkyboxRt ;
        inline  uintptr_t SkyboxUp ;
        inline  uintptr_t StarCount ;
        inline  uintptr_t SunAngularSize ;
        inline  uintptr_t SunTextureId ;
    }

    namespace Sound {
        inline  uintptr_t IsPlaying ;
        inline  uintptr_t Looped ;
        inline  uintptr_t PlaybackSpeed ;
        inline  uintptr_t RollOffMaxDistance ;
        inline  uintptr_t RollOffMinDistance ;
        inline  uintptr_t SoundGroup ;
        inline  uintptr_t SoundId ;
        inline  uintptr_t Volume ;
    }

    namespace SpawnLocation {
        inline  uintptr_t AllowTeamChangeOnTouch ;
        inline  uintptr_t Enabled ;
        inline  uintptr_t ForcefieldDuration ;
        inline  uintptr_t Neutral ;
        inline  uintptr_t TeamColor ;
    }

    namespace SpecialMesh {
        inline  uintptr_t MeshId ;
        inline  uintptr_t Scale ;
    }

    namespace StatsItem {
        inline  uintptr_t Value ;
    }

    namespace SunRaysEffect {
        inline  uintptr_t Enabled ;
        inline  uintptr_t Intensity ;
        inline  uintptr_t Spread ;
    }

    namespace SurfaceAppearance {
        inline  uintptr_t AlphaMode ;
        inline  uintptr_t Color ;
        inline  uintptr_t ColorMap ;
        inline  uintptr_t EmissiveMaskContent ;
        inline  uintptr_t EmissiveStrength ;
        inline  uintptr_t EmissiveTint ;
        inline  uintptr_t MetalnessMap ;
        inline  uintptr_t NormalMap ;
        inline  uintptr_t RoughnessMap ;
    }

    namespace TaskScheduler {
        inline  uintptr_t JobEnd ;
        inline  uintptr_t JobName ;
        inline  uintptr_t JobStart ;
        inline  uintptr_t MaxFPS ;
        inline  uintptr_t Pointer ;
    }

    namespace Team {
        inline  uintptr_t BrickColor ;
    }

    namespace Terrain {
        inline  uintptr_t GrassLength ;
        inline  uintptr_t MaterialColors ;
        inline  uintptr_t WaterColor ;
        inline  uintptr_t WaterReflectance ;
        inline  uintptr_t WaterTransparency ;
        inline  uintptr_t WaterWaveSize ;
        inline  uintptr_t WaterWaveSpeed ;
    }

    namespace Textures {
        inline  uintptr_t Decal_Texture ;
        inline  uintptr_t Texture_Texture ;
    }

    namespace Tool {
        inline  uintptr_t CanBeDropped ;
        inline  uintptr_t Enabled ;
        inline  uintptr_t Grip ;
        inline  uintptr_t ManualActivationOnly ;
        inline  uintptr_t RequiresHandle ;
        inline  uintptr_t TextureId ;
        inline  uintptr_t Tooltip ;
    }

    namespace UnionOperation {
        inline  uintptr_t AssetId ;
    }

    namespace UserInputService {
        inline  uintptr_t WindowInputState ;
    }

    namespace VehicleSeat {
        inline  uintptr_t MaxSpeed ;
        inline  uintptr_t SteerFloat ;
        inline  uintptr_t ThrottleFloat ;
        inline  uintptr_t Torque ;
        inline  uintptr_t TurnSpeed ;
    }

    namespace VisualEngine {
        inline  uintptr_t Dimensions ;
        inline  uintptr_t FakeDataModel ;
        inline  uintptr_t Pointer ;
        inline  uintptr_t RenderView ;
        inline  uintptr_t ViewMatrix ;
    }

    namespace Weld {
        inline  uintptr_t Part0 ;
        inline  uintptr_t Part1 ;
    }

    namespace WeldConstraint {
        inline  uintptr_t Part0 ;
        inline  uintptr_t Part1 ;
    }

    namespace WindowInputState {
        inline  uintptr_t CapsLock ;
        inline  uintptr_t CurrentTextBox ;
    }

    namespace Workspace {
        inline  uintptr_t CurrentCamera ;
        inline  uintptr_t DistributedGameTime ;
        inline  uintptr_t ReadOnlyGravity ;
        inline  uintptr_t World ;
    }

    namespace World {
        inline  uintptr_t AirProperties ;
        inline  uintptr_t FallenPartsDestroyHeight ;
        inline  uintptr_t Gravity ;
        inline  uintptr_t Primitives ;
        inline  uintptr_t worldStepsPerSec ;
    }

}