#pragma once
#include "offsets.h"


bool SetOffset(const std::string& ns, const std::string& name, uintptr_t value)
{
    if (ns == "AirProperties")
    {
        if (name == "AirDensity") Offsets::AirProperties::AirDensity = value;
        else if (name == "GlobalWind") Offsets::AirProperties::GlobalWind = value;
    }
    else if (ns == "AnimationTrack")
    {
        if (name == "Animation") Offsets::AnimationTrack::Animation = value;
        else if (name == "Animator") Offsets::AnimationTrack::Animator = value;
        else if (name == "IsPlaying") Offsets::AnimationTrack::IsPlaying = value;
        else if (name == "Looped") Offsets::AnimationTrack::Looped = value;
        else if (name == "Speed") Offsets::AnimationTrack::Speed = value;
        else if (name == "TimePosition") Offsets::AnimationTrack::TimePosition = value;
    }
    else if (ns == "Animator")
    {
        if (name == "ActiveAnimations") Offsets::Animator::ActiveAnimations = value;
    }
    else if (ns == "Atmosphere")
    {
        if (name == "Color") Offsets::Atmosphere::Color = value;
        else if (name == "Decay") Offsets::Atmosphere::Decay = value;
        else if (name == "Density") Offsets::Atmosphere::Density = value;
        else if (name == "Glare") Offsets::Atmosphere::Glare = value;
        else if (name == "Haze") Offsets::Atmosphere::Haze = value;
        else if (name == "Offset") Offsets::Atmosphere::Offset = value;
    }
    else if (ns == "Attachment")
    {
        if (name == "Position") Offsets::Attachment::Position = value;
    }
    else if (ns == "Attribute")
    {
        if (name == "Key") Offsets::Attribute::Key = value;
        else if (name == "Size") Offsets::Attribute::Size = value;
        else if (name == "Value") Offsets::Attribute::Value = value;
    }
    else if (ns == "AttributesMap")
    {
        if (name == "Attributes") Offsets::AttributesMap::Attributes = value;
        else if (name == "Length") Offsets::AttributesMap::Length = value;
    }
    else if (ns == "BasePart")
    {
        if (name == "CastShadow") Offsets::BasePart::CastShadow = value;
        else if (name == "Color3") Offsets::BasePart::Color3 = value;
        else if (name == "Locked") Offsets::BasePart::Locked = value;
        else if (name == "Massless") Offsets::BasePart::Massless = value;
        else if (name == "Primitive") Offsets::BasePart::Primitive = value;
        else if (name == "Reflectance") Offsets::BasePart::Reflectance = value;
        else if (name == "Shape") Offsets::BasePart::Shape = value;
        else if (name == "Transparency") Offsets::BasePart::Transparency = value;
    }
    else if (ns == "Beam")
    {
        if (name == "Attachment0") Offsets::Beam::Attachment0 = value;
        else if (name == "Attachment1") Offsets::Beam::Attachment1 = value;
        else if (name == "Brightness") Offsets::Beam::Brightness = value;
        else if (name == "CurveSize0") Offsets::Beam::CurveSize0 = value;
        else if (name == "CurveSize1") Offsets::Beam::CurveSize1 = value;
        else if (name == "LightEmission") Offsets::Beam::LightEmission = value;
        else if (name == "LightInfluence") Offsets::Beam::LightInfluence = value;
        else if (name == "Texture") Offsets::Beam::Texture = value;
        else if (name == "TextureLength") Offsets::Beam::TextureLength = value;
        else if (name == "TextureSpeed") Offsets::Beam::TextureSpeed = value;
        else if (name == "Width0") Offsets::Beam::Width0 = value;
        else if (name == "Width1") Offsets::Beam::Width1 = value;
        else if (name == "ZOffset") Offsets::Beam::ZOffset = value;
    }
    else if (ns == "BloomEffect")
    {
        if (name == "Enabled") Offsets::BloomEffect::Enabled = value;
        else if (name == "Intensity") Offsets::BloomEffect::Intensity = value;
        else if (name == "Size") Offsets::BloomEffect::Size = value;
        else if (name == "Threshold") Offsets::BloomEffect::Threshold = value;
    }
    else if (ns == "BlurEffect")
    {
        if (name == "Enabled") Offsets::BlurEffect::Enabled = value;
        else if (name == "Size") Offsets::BlurEffect::Size = value;
    }
    else if (ns == "ByteCode")
    {
        if (name == "Pointer") Offsets::ByteCode::Pointer = value;
        else if (name == "Size") Offsets::ByteCode::Size = value;
    }
    else if (ns == "Camera")
    {
        if (name == "CameraSubject") Offsets::Camera::CameraSubject = value;
        else if (name == "CameraType") Offsets::Camera::CameraType = value;
        else if (name == "FieldOfView") Offsets::Camera::FieldOfView = value;
        else if (name == "ImagePlaneDepth") Offsets::Camera::ImagePlaneDepth = value;
        else if (name == "Position") Offsets::Camera::Position = value;
        else if (name == "Rotation") Offsets::Camera::Rotation = value;
        else if (name == "Viewport") Offsets::Camera::Viewport = value;
        else if (name == "ViewportSize") Offsets::Camera::ViewportSize = value;
    }
    else if (ns == "CharacterMesh")
    {
        if (name == "BaseTextureId") Offsets::CharacterMesh::BaseTextureId = value;
        else if (name == "BodyPart") Offsets::CharacterMesh::BodyPart = value;
        else if (name == "MeshId") Offsets::CharacterMesh::MeshId = value;
        else if (name == "OverlayTextureId") Offsets::CharacterMesh::OverlayTextureId = value;
    }
    else if (ns == "ClickDetector")
    {
        if (name == "MaxActivationDistance") Offsets::ClickDetector::MaxActivationDistance = value;
        else if (name == "MouseIcon") Offsets::ClickDetector::MouseIcon = value;
    }
    else if (ns == "Clothing")
    {
        if (name == "Color3") Offsets::Clothing::Color3 = value;
        else if (name == "Template") Offsets::Clothing::Template = value;
    }
    else if (ns == "ColorCorrectionEffect")
    {
        if (name == "Brightness") Offsets::ColorCorrectionEffect::Brightness = value;
        else if (name == "Contrast") Offsets::ColorCorrectionEffect::Contrast = value;
        else if (name == "Enabled") Offsets::ColorCorrectionEffect::Enabled = value;
        else if (name == "TintColor") Offsets::ColorCorrectionEffect::TintColor = value;
    }
    else if (ns == "ColorGradingEffect")
    {
        if (name == "Enabled") Offsets::ColorGradingEffect::Enabled = value;
        else if (name == "TonemapperPreset") Offsets::ColorGradingEffect::TonemapperPreset = value;
    }
    else if (ns == "DataModel")
    {
        if (name == "CreatorId") Offsets::DataModel::CreatorId = value;
        else if (name == "GameId") Offsets::DataModel::GameId = value;
        else if (name == "GameLoaded") Offsets::DataModel::GameLoaded = value;
        else if (name == "JobId") Offsets::DataModel::JobId = value;
        else if (name == "PlaceId") Offsets::DataModel::PlaceId = value;
        else if (name == "PlaceVersion") Offsets::DataModel::PlaceVersion = value;
        else if (name == "PrimitiveCount") Offsets::DataModel::PrimitiveCount = value;
        else if (name == "ScriptContext") Offsets::DataModel::ScriptContext = value;
        else if (name == "ServerIP") Offsets::DataModel::ServerIP = value;
        else if (name == "ToRenderView1") Offsets::DataModel::ToRenderView1 = value;
        else if (name == "ToRenderView2") Offsets::DataModel::ToRenderView2 = value;
        else if (name == "ToRenderView3") Offsets::DataModel::ToRenderView3 = value;
        else if (name == "Workspace") Offsets::DataModel::Workspace = value;
    }
    else if (ns == "DepthOfFieldEffect")
    {
        if (name == "Enabled") Offsets::DepthOfFieldEffect::Enabled = value;
        else if (name == "FarIntensity") Offsets::DepthOfFieldEffect::FarIntensity = value;
        else if (name == "FocusDistance") Offsets::DepthOfFieldEffect::FocusDistance = value;
        else if (name == "InFocusRadius") Offsets::DepthOfFieldEffect::InFocusRadius = value;
        else if (name == "NearIntensity") Offsets::DepthOfFieldEffect::NearIntensity = value;
    }
    else if (ns == "DragDetector")
    {
        if (name == "ActivatedCursorIcon") Offsets::DragDetector::ActivatedCursorIcon = value;
        else if (name == "CursorIcon") Offsets::DragDetector::CursorIcon = value;
        else if (name == "MaxActivationDistance") Offsets::DragDetector::MaxActivationDistance = value;
        else if (name == "MaxDragAngle") Offsets::DragDetector::MaxDragAngle = value;
        else if (name == "MaxDragTranslation") Offsets::DragDetector::MaxDragTranslation = value;
        else if (name == "MaxForce") Offsets::DragDetector::MaxForce = value;
        else if (name == "MaxTorque") Offsets::DragDetector::MaxTorque = value;
        else if (name == "MinDragAngle") Offsets::DragDetector::MinDragAngle = value;
        else if (name == "MinDragTranslation") Offsets::DragDetector::MinDragTranslation = value;
        else if (name == "ReferenceInstance") Offsets::DragDetector::ReferenceInstance = value;
        else if (name == "Responsiveness") Offsets::DragDetector::Responsiveness = value;
    }
    else if (ns == "FakeDataModel")
    {
        if (name == "Pointer") Offsets::FakeDataModel::Pointer = value;
        else if (name == "RealDataModel") Offsets::FakeDataModel::RealDataModel = value;
    }
    else if (ns == "GuiBase2D")
    {
        if (name == "AbsolutePosition") Offsets::GuiBase2D::AbsolutePosition = value;
        else if (name == "AbsoluteRotation") Offsets::GuiBase2D::AbsoluteRotation = value;
        else if (name == "AbsoluteSize") Offsets::GuiBase2D::AbsoluteSize = value;
    }
    else if (ns == "GuiObject")
    {
        if (name == "BackgroundColor3") Offsets::GuiObject::BackgroundColor3 = value;
        else if (name == "BackgroundTransparency") Offsets::GuiObject::BackgroundTransparency = value;
        else if (name == "BorderColor3") Offsets::GuiObject::BorderColor3 = value;
        else if (name == "Image") Offsets::GuiObject::Image = value;
        else if (name == "LayoutOrder") Offsets::GuiObject::LayoutOrder = value;
        else if (name == "Position") Offsets::GuiObject::Position = value;
        else if (name == "RichText") Offsets::GuiObject::RichText = value;
        else if (name == "Rotation") Offsets::GuiObject::Rotation = value;
        else if (name == "ScreenGui_Enabled") Offsets::GuiObject::ScreenGui_Enabled = value;
        else if (name == "Size") Offsets::GuiObject::Size = value;
        else if (name == "Text") Offsets::GuiObject::Text = value;
        else if (name == "TextColor3") Offsets::GuiObject::TextColor3 = value;
        else if (name == "Visible") Offsets::GuiObject::Visible = value;
        else if (name == "ZIndex") Offsets::GuiObject::ZIndex = value;
    }
    else if (ns == "Humanoid")
    {
        if (name == "AutoJumpEnabled") Offsets::Humanoid::AutoJumpEnabled = value;
        else if (name == "AutoRotate") Offsets::Humanoid::AutoRotate = value;
        else if (name == "AutomaticScalingEnabled") Offsets::Humanoid::AutomaticScalingEnabled = value;
        else if (name == "BreakJointsOnDeath") Offsets::Humanoid::BreakJointsOnDeath = value;
        else if (name == "CameraOffset") Offsets::Humanoid::CameraOffset = value;
        else if (name == "DisplayDistanceType") Offsets::Humanoid::DisplayDistanceType = value;
        else if (name == "DisplayName") Offsets::Humanoid::DisplayName = value;
        else if (name == "EvaluateStateMachine") Offsets::Humanoid::EvaluateStateMachine = value;
        else if (name == "FloorMaterial") Offsets::Humanoid::FloorMaterial = value;
        else if (name == "Health") Offsets::Humanoid::Health = value;
        else if (name == "HealthDisplayDistance") Offsets::Humanoid::HealthDisplayDistance = value;
        else if (name == "HealthDisplayType") Offsets::Humanoid::HealthDisplayType = value;
        else if (name == "HipHeight") Offsets::Humanoid::HipHeight = value;
        else if (name == "HumanoidRootPart") Offsets::Humanoid::HumanoidRootPart = value;
        else if (name == "HumanoidState") Offsets::Humanoid::HumanoidState = value;
        else if (name == "HumanoidStateID") Offsets::Humanoid::HumanoidStateID = value;
        else if (name == "IsWalking") Offsets::Humanoid::IsWalking = value;
        else if (name == "Jump") Offsets::Humanoid::Jump = value;
        else if (name == "JumpHeight") Offsets::Humanoid::JumpHeight = value;
        else if (name == "JumpPower") Offsets::Humanoid::JumpPower = value;
        else if (name == "MaxHealth") Offsets::Humanoid::MaxHealth = value;
        else if (name == "MaxSlopeAngle") Offsets::Humanoid::MaxSlopeAngle = value;
        else if (name == "MoveDirection") Offsets::Humanoid::MoveDirection = value;
        else if (name == "MoveToPart") Offsets::Humanoid::MoveToPart = value;
        else if (name == "MoveToPoint") Offsets::Humanoid::MoveToPoint = value;
        else if (name == "NameDisplayDistance") Offsets::Humanoid::NameDisplayDistance = value;
        else if (name == "NameOcclusion") Offsets::Humanoid::NameOcclusion = value;
        else if (name == "PlatformStand") Offsets::Humanoid::PlatformStand = value;
        else if (name == "PlatformStatePointer") Offsets::Humanoid::PlatformStatePointer = value;
        else if (name == "RequiresNeck") Offsets::Humanoid::RequiresNeck = value;
        else if (name == "RigType") Offsets::Humanoid::RigType = value;
        else if (name == "SeatPart") Offsets::Humanoid::SeatPart = value;
        else if (name == "Sit") Offsets::Humanoid::Sit = value;
        else if (name == "TargetPoint") Offsets::Humanoid::TargetPoint = value;
        else if (name == "UseJumpPower") Offsets::Humanoid::UseJumpPower = value;
        else if (name == "WalkTimer") Offsets::Humanoid::WalkTimer = value;
        else if (name == "Walkspeed") Offsets::Humanoid::Walkspeed = value;
        else if (name == "WalkspeedCheck") Offsets::Humanoid::WalkspeedCheck = value;
    }
    else if (ns == "Instance")
    {
        if (name == "ChildrenEnd") Offsets::Instance::ChildrenEnd = value;
        else if (name == "ChildrenStart") Offsets::Instance::ChildrenStart = value;
        else if (name == "ClassBase") Offsets::Instance::ClassBase = value;
        else if (name == "ClassDescriptor") Offsets::Instance::ClassDescriptor = value;
        else if (name == "ClassDescriptorToClassName") Offsets::Instance::ClassDescriptorToClassName = value;
        else if (name == "ClassName") Offsets::Instance::ClassName = value;
        else if (name == "ComponentMap") Offsets::Instance::ComponentMap = value;
        else if (name == "Name") Offsets::Instance::Name = value;
        else if (name == "NameContainer") Offsets::Instance::NameContainer = value;
        else if (name == "Parent") Offsets::Instance::Parent = value;
        else if (name == "This") Offsets::Instance::This = value;
    }
    else if (ns == "Lighting")
    {
        if (name == "Ambient") Offsets::Lighting::Ambient = value;
        else if (name == "Brightness") Offsets::Lighting::Brightness = value;
        else if (name == "ClockTime") Offsets::Lighting::ClockTime = value;
        else if (name == "ColorShift_Bottom") Offsets::Lighting::ColorShift_Bottom = value;
        else if (name == "ColorShift_Top") Offsets::Lighting::ColorShift_Top = value;
        else if (name == "EnvironmentDiffuseScale") Offsets::Lighting::EnvironmentDiffuseScale = value;
        else if (name == "EnvironmentSpecularScale") Offsets::Lighting::EnvironmentSpecularScale = value;
        else if (name == "ExposureCompensation") Offsets::Lighting::ExposureCompensation = value;
        else if (name == "FogColor") Offsets::Lighting::FogColor = value;
        else if (name == "FogEnd") Offsets::Lighting::FogEnd = value;
        else if (name == "FogStart") Offsets::Lighting::FogStart = value;
        else if (name == "GeographicLatitude") Offsets::Lighting::GeographicLatitude = value;
        else if (name == "GlobalShadows") Offsets::Lighting::GlobalShadows = value;
        else if (name == "GradientBottom") Offsets::Lighting::GradientBottom = value;
        else if (name == "GradientTop") Offsets::Lighting::GradientTop = value;
        else if (name == "LightColor") Offsets::Lighting::LightColor = value;
        else if (name == "LightDirection") Offsets::Lighting::LightDirection = value;
        else if (name == "MoonPosition") Offsets::Lighting::MoonPosition = value;
        else if (name == "OutdoorAmbient") Offsets::Lighting::OutdoorAmbient = value;
        else if (name == "Sky") Offsets::Lighting::Sky = value;
        else if (name == "Source") Offsets::Lighting::Source = value;
        else if (name == "SunPosition") Offsets::Lighting::SunPosition = value;
    }
    else if (ns == "LocalScript")
    {
        if (name == "ByteCode") Offsets::LocalScript::ByteCode = value;
        else if (name == "GUID") Offsets::LocalScript::GUID = value;
        else if (name == "Hash") Offsets::LocalScript::Hash = value;
    }
    else if (ns == "MaterialColors")
    {
        if (name == "Asphalt") Offsets::MaterialColors::Asphalt = value;
        else if (name == "Basalt") Offsets::MaterialColors::Basalt = value;
        else if (name == "Brick") Offsets::MaterialColors::Brick = value;
        else if (name == "Cobblestone") Offsets::MaterialColors::Cobblestone = value;
        else if (name == "Concrete") Offsets::MaterialColors::Concrete = value;
        else if (name == "CrackedLava") Offsets::MaterialColors::CrackedLava = value;
        else if (name == "Glacier") Offsets::MaterialColors::Glacier = value;
        else if (name == "Grass") Offsets::MaterialColors::Grass = value;
        else if (name == "Ground") Offsets::MaterialColors::Ground = value;
        else if (name == "Ice") Offsets::MaterialColors::Ice = value;
        else if (name == "LeafyGrass") Offsets::MaterialColors::LeafyGrass = value;
        else if (name == "Limestone") Offsets::MaterialColors::Limestone = value;
        else if (name == "Mud") Offsets::MaterialColors::Mud = value;
        else if (name == "Pavement") Offsets::MaterialColors::Pavement = value;
        else if (name == "Rock") Offsets::MaterialColors::Rock = value;
        else if (name == "Salt") Offsets::MaterialColors::Salt = value;
        else if (name == "Sand") Offsets::MaterialColors::Sand = value;
        else if (name == "Sandstone") Offsets::MaterialColors::Sandstone = value;
        else if (name == "Slate") Offsets::MaterialColors::Slate = value;
        else if (name == "Snow") Offsets::MaterialColors::Snow = value;
        else if (name == "WoodPlanks") Offsets::MaterialColors::WoodPlanks = value;
    }
    else if (ns == "MeshContentProvider")
    {
        if (name == "AssetID") Offsets::MeshContentProvider::AssetID = value;
        else if (name == "Cache") Offsets::MeshContentProvider::Cache = value;
        else if (name == "LRUCache") Offsets::MeshContentProvider::LRUCache = value;
        else if (name == "MeshData") Offsets::MeshContentProvider::MeshData = value;
        else if (name == "ToMeshData") Offsets::MeshContentProvider::ToMeshData = value;
    }
    else if (ns == "MeshData")
    {
        if (name == "FaceEnd") Offsets::MeshData::FaceEnd = value;
        else if (name == "FaceStart") Offsets::MeshData::FaceStart = value;
        else if (name == "VertexEnd") Offsets::MeshData::VertexEnd = value;
        else if (name == "VertexStart") Offsets::MeshData::VertexStart = value;
    }
    else if (ns == "MeshPart")
    {
        if (name == "MeshId") Offsets::MeshPart::MeshId = value;
        else if (name == "Texture") Offsets::MeshPart::Texture = value;
    }
    else if (ns == "Misc")
    {
        if (name == "Adornee") Offsets::Misc::Adornee = value;
        else if (name == "AnimationId") Offsets::Misc::AnimationId = value;
        else if (name == "StringLength") Offsets::Misc::StringLength = value;
        else if (name == "Value") Offsets::Misc::Value = value;
    }
    else if (ns == "Model")
    {
        if (name == "PrimaryPart") Offsets::Model::PrimaryPart = value;
        else if (name == "Scale") Offsets::Model::Scale = value;
    }
    else if (ns == "ModuleScript")
    {
        if (name == "ByteCode") Offsets::ModuleScript::ByteCode = value;
        else if (name == "GUID") Offsets::ModuleScript::GUID = value;
        else if (name == "Hash") Offsets::ModuleScript::Hash = value;
        else if (name == "IsCoreScript") Offsets::ModuleScript::IsCoreScript = value;
    }
    else if (ns == "MouseService")
    {
        if (name == "InputObject") Offsets::MouseService::InputObject = value;
        else if (name == "InputObject2") Offsets::MouseService::InputObject2 = value;
        else if (name == "MousePosition") Offsets::MouseService::MousePosition = value;
        else if (name == "SensitivityPointer") Offsets::MouseService::SensitivityPointer = value;
    }
    else if (ns == "ParticleEmitter")
    {
        if (name == "Acceleration") Offsets::ParticleEmitter::Acceleration = value;
        else if (name == "Brightness") Offsets::ParticleEmitter::Brightness = value;
        else if (name == "Drag") Offsets::ParticleEmitter::Drag = value;
        else if (name == "Lifetime") Offsets::ParticleEmitter::Lifetime = value;
        else if (name == "LightEmission") Offsets::ParticleEmitter::LightEmission = value;
        else if (name == "LightInfluence") Offsets::ParticleEmitter::LightInfluence = value;
        else if (name == "Rate") Offsets::ParticleEmitter::Rate = value;
        else if (name == "RotSpeed") Offsets::ParticleEmitter::RotSpeed = value;
        else if (name == "Rotation") Offsets::ParticleEmitter::Rotation = value;
        else if (name == "Speed") Offsets::ParticleEmitter::Speed = value;
        else if (name == "SpreadAngle") Offsets::ParticleEmitter::SpreadAngle = value;
        else if (name == "Texture") Offsets::ParticleEmitter::Texture = value;
        else if (name == "TimeScale") Offsets::ParticleEmitter::TimeScale = value;
        else if (name == "VelocityInheritance") Offsets::ParticleEmitter::VelocityInheritance = value;
        else if (name == "ZOffset") Offsets::ParticleEmitter::ZOffset = value;
    }
    else if (ns == "Player")
    {
        if (name == "AccountAge") Offsets::Player::AccountAge = value;
        else if (name == "CameraMode") Offsets::Player::CameraMode = value;
        else if (name == "DisplayName") Offsets::Player::DisplayName = value;
        else if (name == "HealthDisplayDistance") Offsets::Player::HealthDisplayDistance = value;
        else if (name == "LocalPlayer") Offsets::Player::LocalPlayer = value;
        else if (name == "LocaleId") Offsets::Player::LocaleId = value;
        else if (name == "MaxZoomDistance") Offsets::Player::MaxZoomDistance = value;
        else if (name == "MinZoomDistance") Offsets::Player::MinZoomDistance = value;
        else if (name == "ModelInstance") Offsets::Player::ModelInstance = value;
        else if (name == "Mouse") Offsets::Player::Mouse = value;
        else if (name == "NameDisplayDistance") Offsets::Player::NameDisplayDistance = value;
        else if (name == "Team") Offsets::Player::Team = value;
        else if (name == "TeamColor") Offsets::Player::TeamColor = value;
        else if (name == "UserId") Offsets::Player::UserId = value;
    }
    else if (ns == "PlayerConfigurer")
    {
        if (name == "Pointer") Offsets::PlayerConfigurer::Pointer = value;
    }
    else if (ns == "PlayerMouse")
    {
        if (name == "Icon") Offsets::PlayerMouse::Icon = value;
        else if (name == "Workspace") Offsets::PlayerMouse::Workspace = value;
    }
    else if (ns == "Primitive")
    {
        if (name == "AssemblyAngularVelocity") Offsets::Primitive::AssemblyAngularVelocity = value;
        else if (name == "AssemblyLinearVelocity") Offsets::Primitive::AssemblyLinearVelocity = value;
        else if (name == "Flags") Offsets::Primitive::Flags = value;
        else if (name == "Material") Offsets::Primitive::Material = value;
        else if (name == "Owner") Offsets::Primitive::Owner = value;
        else if (name == "Position") Offsets::Primitive::Position = value;
        else if (name == "Rotation") Offsets::Primitive::Rotation = value;
        else if (name == "Size") Offsets::Primitive::Size = value;
        else if (name == "Validate") Offsets::Primitive::Validate = value;
    }
    else if (ns == "PrimitiveFlags")
    {
        if (name == "Anchored") Offsets::PrimitiveFlags::Anchored = value;
        else if (name == "CanCollide") Offsets::PrimitiveFlags::CanCollide = value;
        else if (name == "CanQuery") Offsets::PrimitiveFlags::CanQuery = value;
        else if (name == "CanTouch") Offsets::PrimitiveFlags::CanTouch = value;
    }
    else if (ns == "ProximityPrompt")
    {
        if (name == "ActionText") Offsets::ProximityPrompt::ActionText = value;
        else if (name == "Enabled") Offsets::ProximityPrompt::Enabled = value;
        else if (name == "GamepadKeyCode") Offsets::ProximityPrompt::GamepadKeyCode = value;
        else if (name == "HoldDuration") Offsets::ProximityPrompt::HoldDuration = value;
        else if (name == "KeyCode") Offsets::ProximityPrompt::KeyCode = value;
        else if (name == "MaxActivationDistance") Offsets::ProximityPrompt::MaxActivationDistance = value;
        else if (name == "ObjectText") Offsets::ProximityPrompt::ObjectText = value;
        else if (name == "RequiresLineOfSight") Offsets::ProximityPrompt::RequiresLineOfSight = value;
    }
    else if (ns == "RenderJob")
    {
        if (name == "FakeDataModel") Offsets::RenderJob::FakeDataModel = value;
        else if (name == "RealDataModel") Offsets::RenderJob::RealDataModel = value;
        else if (name == "RenderView") Offsets::RenderJob::RenderView = value;
    }
    else if (ns == "RenderView")
    {
        if (name == "DeviceD3D11") Offsets::RenderView::DeviceD3D11 = value;
        else if (name == "LightingValid") Offsets::RenderView::LightingValid = value;
        else if (name == "SkyValid") Offsets::RenderView::SkyValid = value;
        else if (name == "VisualEngine") Offsets::RenderView::VisualEngine = value;
    }
    else if (ns == "RunService")
    {
        if (name == "HeartbeatFPS") Offsets::RunService::HeartbeatFPS = value;
        else if (name == "HeartbeatTask") Offsets::RunService::HeartbeatTask = value;
    }
    else if (ns == "Script")
    {
        if (name == "ByteCode") Offsets::Script::ByteCode = value;
        else if (name == "GUID") Offsets::Script::GUID = value;
        else if (name == "Hash") Offsets::Script::Hash = value;
    }
    else if (ns == "ScriptContext")
    {
        if (name == "RequireBypass") Offsets::ScriptContext::RequireBypass = value;
    }
    else if (ns == "Seat")
    {
        if (name == "Occupant") Offsets::Seat::Occupant = value;
    }
    else if (ns == "Sky")
    {
        if (name == "MoonAngularSize") Offsets::Sky::MoonAngularSize = value;
        else if (name == "MoonTextureId") Offsets::Sky::MoonTextureId = value;
        else if (name == "SkyboxBk") Offsets::Sky::SkyboxBk = value;
        else if (name == "SkyboxDn") Offsets::Sky::SkyboxDn = value;
        else if (name == "SkyboxFt") Offsets::Sky::SkyboxFt = value;
        else if (name == "SkyboxLf") Offsets::Sky::SkyboxLf = value;
        else if (name == "SkyboxOrientation") Offsets::Sky::SkyboxOrientation = value;
        else if (name == "SkyboxRt") Offsets::Sky::SkyboxRt = value;
        else if (name == "SkyboxUp") Offsets::Sky::SkyboxUp = value;
        else if (name == "StarCount") Offsets::Sky::StarCount = value;
        else if (name == "SunAngularSize") Offsets::Sky::SunAngularSize = value;
        else if (name == "SunTextureId") Offsets::Sky::SunTextureId = value;
    }
    else if (ns == "Sound")
    {
        if (name == "IsPlaying") Offsets::Sound::IsPlaying = value;
        else if (name == "Looped") Offsets::Sound::Looped = value;
        else if (name == "PlaybackSpeed") Offsets::Sound::PlaybackSpeed = value;
        else if (name == "RollOffMaxDistance") Offsets::Sound::RollOffMaxDistance = value;
        else if (name == "RollOffMinDistance") Offsets::Sound::RollOffMinDistance = value;
        else if (name == "SoundGroup") Offsets::Sound::SoundGroup = value;
        else if (name == "SoundId") Offsets::Sound::SoundId = value;
        else if (name == "Volume") Offsets::Sound::Volume = value;
    }
    else if (ns == "SpawnLocation")
    {
        if (name == "AllowTeamChangeOnTouch") Offsets::SpawnLocation::AllowTeamChangeOnTouch = value;
        else if (name == "Enabled") Offsets::SpawnLocation::Enabled = value;
        else if (name == "ForcefieldDuration") Offsets::SpawnLocation::ForcefieldDuration = value;
        else if (name == "Neutral") Offsets::SpawnLocation::Neutral = value;
        else if (name == "TeamColor") Offsets::SpawnLocation::TeamColor = value;
    }
    else if (ns == "SpecialMesh")
    {
        if (name == "MeshId") Offsets::SpecialMesh::MeshId = value;
        else if (name == "Scale") Offsets::SpecialMesh::Scale = value;
    }
    else if (ns == "StatsItem")
    {
        if (name == "Value") Offsets::StatsItem::Value = value;
    }
    else if (ns == "SunRaysEffect")
    {
        if (name == "Enabled") Offsets::SunRaysEffect::Enabled = value;
        else if (name == "Intensity") Offsets::SunRaysEffect::Intensity = value;
        else if (name == "Spread") Offsets::SunRaysEffect::Spread = value;
    }
    else if (ns == "SurfaceAppearance")
    {
        if (name == "AlphaMode") Offsets::SurfaceAppearance::AlphaMode = value;
        else if (name == "Color") Offsets::SurfaceAppearance::Color = value;
        else if (name == "ColorMap") Offsets::SurfaceAppearance::ColorMap = value;
        else if (name == "EmissiveMaskContent") Offsets::SurfaceAppearance::EmissiveMaskContent = value;
        else if (name == "EmissiveStrength") Offsets::SurfaceAppearance::EmissiveStrength = value;
        else if (name == "EmissiveTint") Offsets::SurfaceAppearance::EmissiveTint = value;
        else if (name == "MetalnessMap") Offsets::SurfaceAppearance::MetalnessMap = value;
        else if (name == "NormalMap") Offsets::SurfaceAppearance::NormalMap = value;
        else if (name == "RoughnessMap") Offsets::SurfaceAppearance::RoughnessMap = value;
    }
    else if (ns == "TaskScheduler")
    {
        if (name == "JobEnd") Offsets::TaskScheduler::JobEnd = value;
        else if (name == "JobName") Offsets::TaskScheduler::JobName = value;
        else if (name == "JobStart") Offsets::TaskScheduler::JobStart = value;
        else if (name == "MaxFPS") Offsets::TaskScheduler::MaxFPS = value;
        else if (name == "Pointer") Offsets::TaskScheduler::Pointer = value;
    }
    else if (ns == "Team")
    {
        if (name == "BrickColor") Offsets::Team::BrickColor = value;
    }
    else if (ns == "Terrain")
    {
        if (name == "GrassLength") Offsets::Terrain::GrassLength = value;
        else if (name == "MaterialColors") Offsets::Terrain::MaterialColors = value;
        else if (name == "WaterColor") Offsets::Terrain::WaterColor = value;
        else if (name == "WaterReflectance") Offsets::Terrain::WaterReflectance = value;
        else if (name == "WaterTransparency") Offsets::Terrain::WaterTransparency = value;
        else if (name == "WaterWaveSize") Offsets::Terrain::WaterWaveSize = value;
        else if (name == "WaterWaveSpeed") Offsets::Terrain::WaterWaveSpeed = value;
    }
    else if (ns == "Textures")
    {
        if (name == "Decal_Texture") Offsets::Textures::Decal_Texture = value;
        else if (name == "Texture_Texture") Offsets::Textures::Texture_Texture = value;
    }
    else if (ns == "Tool")
    {
        if (name == "CanBeDropped") Offsets::Tool::CanBeDropped = value;
        else if (name == "Enabled") Offsets::Tool::Enabled = value;
        else if (name == "Grip") Offsets::Tool::Grip = value;
        else if (name == "ManualActivationOnly") Offsets::Tool::ManualActivationOnly = value;
        else if (name == "RequiresHandle") Offsets::Tool::RequiresHandle = value;
        else if (name == "TextureId") Offsets::Tool::TextureId = value;
        else if (name == "Tooltip") Offsets::Tool::Tooltip = value;
    }
    else if (ns == "UnionOperation")
    {
        if (name == "AssetId") Offsets::UnionOperation::AssetId = value;
    }
    else if (ns == "UserInputService")
    {
        if (name == "WindowInputState") Offsets::UserInputService::WindowInputState = value;
    }
    else if (ns == "VehicleSeat")
    {
        if (name == "MaxSpeed") Offsets::VehicleSeat::MaxSpeed = value;
        else if (name == "SteerFloat") Offsets::VehicleSeat::SteerFloat = value;
        else if (name == "ThrottleFloat") Offsets::VehicleSeat::ThrottleFloat = value;
        else if (name == "Torque") Offsets::VehicleSeat::Torque = value;
        else if (name == "TurnSpeed") Offsets::VehicleSeat::TurnSpeed = value;
    }
    else if (ns == "VisualEngine")
    {
        if (name == "Dimensions") Offsets::VisualEngine::Dimensions = value;
        else if (name == "FakeDataModel") Offsets::VisualEngine::FakeDataModel = value;
        else if (name == "Pointer") Offsets::VisualEngine::Pointer = value;
        else if (name == "RenderView") Offsets::VisualEngine::RenderView = value;
        else if (name == "ViewMatrix") Offsets::VisualEngine::ViewMatrix = value;
    }
    else if (ns == "Weld")
    {
        if (name == "Part0") Offsets::Weld::Part0 = value;
        else if (name == "Part1") Offsets::Weld::Part1 = value;
    }
    else if (ns == "WeldConstraint")
    {
        if (name == "Part0") Offsets::WeldConstraint::Part0 = value;
        else if (name == "Part1") Offsets::WeldConstraint::Part1 = value;
    }
    else if (ns == "WindowInputState")
    {
        if (name == "CapsLock") Offsets::WindowInputState::CapsLock = value;
        else if (name == "CurrentTextBox") Offsets::WindowInputState::CurrentTextBox = value;
    }
    else if (ns == "Workspace")
    {
        if (name == "CurrentCamera") Offsets::Workspace::CurrentCamera = value;
        else if (name == "DistributedGameTime") Offsets::Workspace::DistributedGameTime = value;
        else if (name == "ReadOnlyGravity") Offsets::Workspace::ReadOnlyGravity = value;
        else if (name == "World") Offsets::Workspace::World = value;
    }
    else if (ns == "World")
    {
        if (name == "AirProperties") Offsets::World::AirProperties = value;
        else if (name == "FallenPartsDestroyHeight") Offsets::World::FallenPartsDestroyHeight = value;
        else if (name == "Gravity") Offsets::World::Gravity = value;
        else if (name == "Primitives") Offsets::World::Primitives = value;
        else if (name == "worldStepsPerSec") Offsets::World::worldStepsPerSec = value;
    }

    return true;
}