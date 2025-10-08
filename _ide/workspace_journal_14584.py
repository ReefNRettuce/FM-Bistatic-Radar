# 2025-10-01T18:42:03.922719400
import vitis

client = vitis.create_client()
client.set_workspace(path="FM-Bistatic-Radar")

comp = client.get_component(name="fir_filter")
comp.run(operation="C_SIMULATION")

comp.run(operation="SYNTHESIS")

comp.run(operation="SYNTHESIS")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="SYNTHESIS")

comp.run(operation="CO_SIMULATION")

comp = client.create_hls_component(name = "Joint_Process_Estimator",cfg_file = ["hls_config.cfg"],template = "empty_hls_component")

vitis.dispose()

