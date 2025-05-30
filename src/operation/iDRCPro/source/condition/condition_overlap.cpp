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

#include "condition_manager.h"
#include "engine_layout.h"
#include "idm.h"

namespace idrc {

void DrcConditionManager::checkOverlap(std::string layer, DrcEngineLayout* layout)
{
  if (_check_select.find(ViolationEnumType::kShort) == _check_select.end()) {
    return;
  }
  DEBUGOUTPUT("");
  DEBUGOUTPUT("layer " << layer);
#ifndef DEBUGCLOSE_OVERLAP
  ieda::Stats states;
  auto& overlap = layout->get_layout()->get_engine()->getOverlap();
  for (auto& overlap_polygon : overlap) {
    ieda_solver::GeometryRect overlap_violation_rect;
    ieda_solver::envelope(overlap_violation_rect, overlap_polygon);
    addViolation(overlap_violation_rect, layer, ViolationEnumType::kShort);
  }
  DEBUGOUTPUT(DEBUGHIGHLIGHT("Metal Short:\t") << overlap.size() << "\ttime = " << states.elapsedRunTime()
                                               << "\tmemory = " << states.memoryDelta());
#endif
}

}  // namespace idrc