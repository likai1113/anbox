/*
 * Copyright (C) 2016 Simon Fels <morphis@gravedo.de>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3, as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranties of
 * MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "anbox/android/ip_config_builder.h"
#include "anbox/common/binder_device_allocator.h"
#include "anbox/common/binder_device.h"
#include "anbox/container/docker_container.h"
#include "anbox/system_configuration.h"
#include "anbox/logger.h"
#include "anbox/utils.h"

#include <map>
#include <stdexcept>
#include <fstream>
#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/throw_exception.hpp>

#include <sys/capability.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include <unistd.h>

namespace fs = boost::filesystem;

namespace anbox::container {

DockerContainer::DockerContainer(): state_(State::inactive){}

DockerContainer::~DockerContainer() {
  stop();
}

void DockerContainer::start(const Configuration &configuration) {
  state_ = State::running;
  auto bind_mounts = configuration.bind_mounts;
  auto devices = configuration.devices;
}

void DockerContainer::stop() {
  state_ = State::inactive;
}

Container::State DockerContainer::state() { return state_; }
}
