#ifndef PROJECTION_PC_H
#define PROJECTION_PC_H 

#include <iostream>
#include <opencv.hpp>
#include <vector>
#include <array>
#include <cmath>
#include <functional>
#include <omp.h>
#include <algorithm>

#include "member_check.hpp"

namespace ppcc
{

template <typename Point_T>
struct LidarProjectionParams 
{
    int projection_height;
    int projection_width;
    int real_lidar_height;
    int real_lidar_width;
    float horizontal_fov;
    float vertical_fov;
    float min_elevation;
    float max_elevation;
    float max_distance;
    float min_distance;
    std::vector<float> elevation_list;
    std::function<float(const Point_T&)> azimuth_calculator;
    std::function<float(const Point_T&)> elevation_calculator;
    int max_threads = omp_get_max_threads();
    
};

template <typename Point_T>
class ProjectionPC 
{
public:
    explicit ProjectionPC(const LidarProjectionParams<Point_T>& params);
    virtual ~ProjectionPC() = default;
    ProjectionPC& operator=(const ProjectionPC& other) = delete;
    ProjectionPC(const ProjectionPC& other) = delete;

    bool SphericalProjection(const std::vector<Point_T>& points_vec, cv::Mat& projection_img)
    {
        if(points_vec.empty())
            return false;
        SphericalProjectionInternal(points_vec.data(), points_vec.size(), projection_img);
        return true;
    }
    bool CylindricalProjection(const std::vector<Point_T>& points_vec, cv::Mat& projection_img)
    {
        if(points_vec.empty())
            return false;
        CylindricalProjectionInternal(points_vec.data(), points_vec.size(), projection_img);
        return true;
    }
    template <std::size_t N>
    bool SphericalProjection(const std::array<Point_T, N>& points_array, int size, cv::Mat& projection_img)
    {
        if(size <= 0 || static_cast<std::size_t>(size) > N)
            return false;
        SphericalProjectionInternal(points_array.data(), size, projection_img);
        return true;
    }
    template <std::size_t N>
    bool CylindricalProjection(const std::array<Point_T, N>& points_array, int size, cv::Mat& projection_img)
    {
        if(size <= 0 || static_cast<std::size_t>(size) > N)
            return false;
        CylindricalProjectionInternal(points_array.data(), size, projection_img);
        return true;
    }

private:
    inline void SphericalProjectionInternal(const Point_T* points_ptr, int size, cv::Mat& projection_img); 
    inline void CylindricalProjectionInternal(const Point_T* points_ptr, int size, cv::Mat& projection_img); 
    inline void CalculateAzimuthElevation(const Point_T& point, float& azimuth, float& elevation) const;
    inline int FindMatchingChannel(float elevation) const;
    inline uint8_t NormalizeDistance(float distance) const;
    inline uint8_t NormalizeCoord(float coord, float min_coord, float max_coord, float range_inv) const;
    void InitElevationList();
    void PrecomputeConstants();
    static inline float DefaultAzimuthCalculator(const Point_T& point);
    static inline float DefaultElevationCalculator(const Point_T& point);

private:
    LidarProjectionParams<Point_T> params_;
    std::vector<float> elevation_list_;
    float half_horizontal_fov_;
    float horizontal_fov_inv_;
    float vertical_fov_inv_;
    float distance_range_;
    float distance_range_inv_;
    float x_range_;
    float x_range_inv_;
    float y_range_;
    float y_range_inv_;
    float z_range_;
    float z_range_inv_;
    float min_x_;
    float min_y_;
    float min_z_;
    float max_z_;
};

}

#endif // PROJECTION_PC_H