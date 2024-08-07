// ***************************************************************************************
// Copyright (c) 2023-2025 Peng Cheng Laboratory
// Copyright (c) 2023-2025 Institute of Computing Technology, Chinese Academy of Sciences
// Copyright (c) 2023-2025 Beijing Institute of Open Source Chip
//
// iEDA is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
// http://license.coscl.org.cn/MulanPSL2
//
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
//
// See the Mulan PSL v2 for more details.
// ***************************************************************************************
#pragma once

#include "drc_basic_point.h"

namespace idrc {

class ScanlinePoint
{
 public:
  ScanlinePoint(DrcBasicPoint* point, int side_id, bool is_forward, bool is_start, ScanlinePoint* pair = nullptr)
      : _point(point), _side_id(side_id), _is_forward(is_forward), _is_new(true), _is_start(is_start), _pair(pair)
  {
  }

  // getter
  DrcBasicPoint* get_point() { return _point; }
  ScanlinePoint* get_pair() { return _pair; }
  bool get_is_forward() { return _is_forward; }
  bool get_is_new() { return _is_new; }
  bool get_is_start() { return _is_start; }

  int get_x() { return _point->get_x(); }
  int get_y() { return _point->get_y(); }
  int get_id() { return _point->get_polygon_id(); }
  int get_side_id() { return _side_id; }

  // setter
  void set_point(DrcBasicPoint* point) { _point = point; }
  void set_pair(ScanlinePoint* pair) { _pair = pair; }
  void set_is_forward(bool is_forward) { _is_forward = is_forward; }
  void set_is_new(bool is_new) { _is_new = is_new; }
  void set_is_start(bool is_start) { _is_start = is_start; }

 private:
  DrcBasicPoint* _point;
  int _side_id;

  bool _is_forward;
  bool _is_new;
  bool _is_start;

  ScanlinePoint* _pair;
};

template <typename T>
struct ComparePointByX
{
  bool operator()(T* p1, T* p2)
  {
    if (p1->get_x() == p2->get_x()) {
      return p1->get_y() > p2->get_y();
    }
    return p1->get_x() < p2->get_x();
  }
};

template <typename T>
struct ComparePointByY
{
  bool operator()(T* p1, T* p2)
  {
    if (p1->get_y() == p2->get_y()) {
      return p1->get_x() < p2->get_x();
    }
    return p1->get_y() < p2->get_y();
  }
};

struct CompareScanlinePoint
{
  virtual bool operator()(ScanlinePoint* p1, ScanlinePoint* p2) = 0;

  virtual ~CompareScanlinePoint() {}
};

struct CompareScanlinePointByX : public CompareScanlinePoint
{
  bool operator()(ScanlinePoint* p1, ScanlinePoint* p2) override
  {
    if (p1->get_point()->get_x() == p2->get_point()->get_x()) {
      if (p1->get_point()->get_y() == p2->get_point()->get_y()) {
        if (p1->get_is_forward() == p2->get_is_forward()) {
          return p1->get_id() < p2->get_id();
        }
        return p1->get_is_forward() > p2->get_is_forward();
      }
      return p1->get_point()->get_y() < p2->get_point()->get_y();
    }
    return p1->get_point()->get_x() < p2->get_point()->get_x();
  }
};

struct CompareScanlinePointByY : public CompareScanlinePoint
{
  bool operator()(ScanlinePoint* p1, ScanlinePoint* p2) override
  {
    if (p1->get_point()->get_y() == p2->get_point()->get_y()) {
      if (p1->get_point()->get_x() == p2->get_point()->get_x()) {
        if (p1->get_is_forward() == p2->get_is_forward()) {
          return p1->get_id() < p2->get_id();
        }
        return p1->get_is_forward() > p2->get_is_forward();
      }
      return p1->get_point()->get_x() < p2->get_point()->get_x();
    }
    return p1->get_point()->get_y() < p2->get_point()->get_y();
  }
};

struct CompareScanlinePointHorizontal : public CompareScanlinePoint
{
  bool operator()(ScanlinePoint* p1, ScanlinePoint* p2) override
  {
    if (p1->get_point()->get_y() == p2->get_point()->get_y()) {
      if (p1->get_is_forward() == p2->get_is_forward()) {
        return p1->get_id() < p2->get_id();
      }
      return p1->get_is_forward() > p2->get_is_forward();
    }
    return p1->get_point()->get_y() < p2->get_point()->get_y();
  }
};

struct CompareScanlinePointVertical : public CompareScanlinePoint
{
  bool operator()(ScanlinePoint* p1, ScanlinePoint* p2) override
  {
    if (p1->get_point()->get_x() == p2->get_point()->get_x()) {
      if (p1->get_is_forward() == p2->get_is_forward()) {
        return p1->get_id() < p2->get_id();
      }
      return p1->get_is_forward() > p2->get_is_forward();
    }
    return p1->get_point()->get_x() < p2->get_point()->get_x();
  }
};

}  // namespace idrc
