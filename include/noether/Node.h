#ifndef NOETHER_NODE_H
#define NOETHER_NODE_H

#include "noether/Network.h"
#include "noether/Tensor.h"
#include "noether/Train.h"

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace noether {

/// This is the non-templated part of the compute node.
class NodeBase {
public:
  /// \returns a descriptive name for the operation.
  virtual std::string getName() const = 0;

  /// Does the forward propagation.
  virtual void forward() = 0;

  /// Does the backwards propagation.
  virtual void backward() = 0;
};

/// Represents a node in the network compute graph.
class TrainableNode : public NodeBase {
protected:
  /// The filter output.
  TrainableData output_;

public:
  TrainableNode(Network *N) { N->registerDerivTensor(this, &output_); }

  /// \returns the output of a node in the compute graph.
  TrainableData &getOutput() { return output_; }

  /// \returns the dimension of the tensor.
  std::tuple<size_t, size_t, size_t> dims() const { return output_.dims(); }

  /// \returns the number of elements in the tensor.
  size_t size() const { return output_.size(); }
};
}

#endif // NOETHER_NODE_H
