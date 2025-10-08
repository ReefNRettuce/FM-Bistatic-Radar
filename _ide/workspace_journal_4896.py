# 2025-10-07T20:41:51.688104
import vitis

client = vitis.create_client()
client.set_workspace(path="FM-Bistatic-Radar")

comp = client.get_component(name="Joint_Process_Estimator")
comp.run(operation="C_SIMULATION")

vitis.dispose()

